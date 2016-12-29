//
// Object.cpp for rtype in /home/rochon_k/rendu/rtype/server/src
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:55:22 2016 kevin rochon
// Last update Mon Dec 19 18:49:26 2016 kevin rochon
//

#include <stdexcept>
#include "Object.hh"

Object::Object()
{
}

Object::Object(const int id, const Object::Type &type, const int hp, const int move_x, const int move_y) :
    _id(id), _type(type), _hp(hp), _movement(move_x, move_y)
{
}

Object::~Object()
{
    while (_components.begin() != _components.end())
    {
        delete *(_components.begin());
        _components.erase(_components.begin());
    }
}

const std::vector<AComponent*>	&Object::getComponents() const
{
  return (this->_components);
}

int			Object::getId() const
{
  return (this->_id);
}

Object::Type		Object::getType() const
{
  return (this->_type);
}

int			Object::getHp() const
{
  return (this->_hp);
}

const std::pair<int, int> &Object::getMovement() const
{
    return (_movement);
}

void			Object::setComponents(const std::vector<AComponent*> &components)
{
  this->_components = components;
}

void              Object::addComponent(AComponent *component)
{
    this->_components.push_back(component);
}

void			Object::setId(int id)
{
  this->_id = id;
}

void			Object::setType(const Object::Type &type)
{
  this->_type = type;
}

void			Object::setHp(int hp)
{
  this->_hp = hp;
}

void    Object::setMovement(const int move_x, const int move_y)
{
    _movement = std::pair<int, int>(move_x, move_y);
}

bool    operator==(const Object &a, const Object &b)
{
    return (a.getId() == b.getId());
}

bool    operator<(const Object &a, const Object &b)
{
    return (a.getId() < b.getId());
}

std::ostream	                        &operator<<(std::ostream &os, const Object::Type &type)
{
    switch (type)
    {
        case Object::Type::PLAYER :
            os << "Player";
            break;
        case Object::Type::ENEMY :
            os << "Enemy";
            break;
        case Object::Type::OBSTACLE :
            os << "Obstacle";
            break;
        case Object::Type::ENEMYBULLET :
            os << "Enemy bullet";
            break;
        case Object::Type::PLAYERBULLET :
            os << "Player bullet";
            break;
        case Object::Type::POWERUP :
            os << "Power-Up";
            break;
        case Object::Type::NONE :
            os << "None";
            break;
        default:
            os << "Invalid type";
            break;
    }
    return (os);
}

std::ostream	&operator<<(std::ostream &os, const Object &obj)
{
    std::vector<AComponent*> components(obj.getComponents());

    os << "ID: " << obj.getId() << std::endl;
    os << "Type: " << obj.getType() << std::endl;
    os << "HP: " << obj.getHp() << std::endl;
    os << "Components:" << std::endl << "--Component list--" << std::endl << std::endl;
    for (std::vector<AComponent*>::const_iterator it = components.begin(); it != components.end(); ++it) {
        const AComponent *component = *it;
        try {
            switch (component->getId()) {
                case AComponent::Type::HITBOX :
                    std::cout << *(dynamic_cast<const Hitbox*>(component)) << std::endl;
                    break;
                case AComponent::Type::SPRITE :
                    std::cout << *(dynamic_cast<const Sprite*>(component)) << std::endl;
                    break;
                default :
                    std::cout << "Invalid component type." << std::endl;
                    break;
            }
        }
        catch (const std::bad_cast &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    os << "--!Component list--" << std::endl;
    return (os);
}