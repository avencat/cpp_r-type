#include "Object.hpp"

Object::Object()
{
}

Object::~Object()
{
}

const std::string				&Object::getName() const
{
	return (this->name);
}

void							Object::setName(const std::string &_name)
{
	this->name = _name;
}

const std::list<AComponent>		&Object::getComponents() const
{
	return (components);
}

void							Object::addAComponent(int _id, const Sprite::TypeSpriteEnum &_type)
{
	AComponent		tmp;

	components.push_back(tmp);
	components.back().setId(_id);
	components.back().setSprite(_type);
}

const AComponent				&Object::getComponent(int _id) const
{
	AComponent		tmp;

	for (std::list<AComponent>::const_iterator i = components.begin(); i != components.end(); i++) {
		if ((*i).getId() == _id) {
			tmp = (*i);
		}
	}
	return (tmp);
}

const std::pair<int, int>		&Object::getPos() const
{
	return (pos);
}

void							Object::setPos(int ft, int sd)
{
	pos.first = ft;
	pos.second = sd;
}