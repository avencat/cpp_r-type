//
// Hitbox.cpp for rtype in /home/rochon_k/rendu/rtype/server/src
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:44:52 2016 kevin rochon
// Last update Mon Dec 19 07:40:12 2016 kevin rochon
//

#include "Hitbox.hh"

Hitbox::Hitbox(const int id) : AComponent(id)
{

}

Hitbox::~Hitbox()
{

}

std::pair<int, int>	Hitbox::getPos()
{
  return (this->_pos);
}

int			Hitbox::getSize()
{
  return (this->_size);
}

void			Hitbox::setPos(std::pair<int, int> pos)
{
  this->_pos = pos;
}

void			Hitbox::setSize(int size)
{
  this->_size = size;
}
