#include "..\inc\Object.hpp"

Object::Object()
{
}

Object::~Object()
{
}

const std::string &Object::getName() const
{
	return (this->name);
}

void Object::setName(const std::string &_name)
{
	this->name = _name;
}
