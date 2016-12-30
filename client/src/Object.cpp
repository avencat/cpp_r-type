#include "Object.hpp"

Object::Object()
{
}

Object::Object(const long &_longName, const sf::Vector2i &_pos, const sf::Vector2i &_dir, const int &_id)
{
	longName = _longName;
	pos = _pos;
	dir = _dir;
	id = _id;
}

Object::~Object()
{
}

const std::list<AComponent>		&Object::getComponents() const
{
	return (components);
}

void							Object::addAComponent(const int &_id, const Sprite::TypeSpriteEnum &_type, const int &lvl)
{
	AComponent		tmp;

	components.push_back(tmp);
	components.back().setId(_id);
	components.back().setSprite(_type, lvl);
}

const AComponent				&Object::getComponent(const int &_id) const
{
	for (std::list<AComponent>::const_iterator i = components.begin(); i != components.end(); i++) {
		if ((*i).getId() == _id) {
			return (*i);
		}
	}
	return (component);
}

const sf::Vector2i				&Object::getPos() const
{
	return (pos);
}

void							Object::setPos(const int &_x, const int &_y)
{
	pos.x = _x;
	pos.y = _y;
	for (std::list<AComponent>::iterator i = components.begin(); i != components.end(); i++) {
		(*i).setPosition(_x, _y);
	}
}

void							Object::setLife(const int &_life)
{
	life = _life;
}

const int						&Object::getLife() const
{
	return (life);
}

void							Object::setScore(const int &_score)
{
	score = _score;
}

const int						&Object::getScore() const
{
	return (score);
}

const long &Object::getLongName() const
{
	return (this->longName);
}

void Object::setLongName(const long &name)
{
	this->longName = name;
}

const int &Object::getId() const
{
	return (this->id);
}

void Object::setId(const int &id)
{
	this->id = id;
}
