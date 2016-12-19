//
// Object.cpp for rtype in /home/rochon_k/rendu/rtype/server/src
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:55:22 2016 kevin rochon
// Last update Mon Dec 19 18:49:26 2016 kevin rochon
//

#include "Object.hh"

Object::Object()
{

}

Object::~Object()
{

}

std::list<AComponent>	Object::getComponents() const
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

void			Object::setComponents(std::list<AComponent> components)
{
  this->_components = components;
}

void			Object::setId(int id)
{
  this->_id = id;
}

void			Object::setType(Object::Type type)
{
  this->_type = type;
}

void			Object::setHp(int hp)
{
  this->_hp = hp;
}
