//
// Sprite.cpp for rtype in /home/rochon_k/rendu/rtype/server/src
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:45:04 2016 kevin rochon
// Last update Mon Dec 19 17:05:50 2016 kevin rochon
//

#include "Sprite.hh"

Sprite::Sprite(const int id, const std::string name) : AComponent(id), _name(name)
{

}

Sprite::~Sprite()
{

}

std::pair<int, int>	Sprite::getPos() const
{
  return (this->_pos);
}

std::string		Sprite::getName() const
{
  return (this->_name);
}

void			Sprite::setPos(int x , int y)
{
  std::pair <int, int> pos(x, y);

  this->_pos = pos;
}

void			Sprite::setName(std::string name)
{
  this->_name = name;
}
