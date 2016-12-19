//
// Sprite.cpp for rtype in /home/rochon_k/rendu/rtype/server/src
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:45:04 2016 kevin rochon
// Last update Mon Dec 19 08:14:21 2016 kevin rochon
//

#include "Sprite.hh"

Sprite::Sprite(const int id) : AComponent(id)
{

}

Sprite::~Sprite()
{

}

std::pair<int, int>	Sprite::getPos()
{
  return (this->_pos);
}

std::string		Sprite::getName()
{
  return (this->_name);
}

void			Sprite::setPos(std::pair<int, int> pos)
{
  this->_pos = pos;
}

void			Sprite::setName(std::string name)
{
  this->_name = name;
}
