//
// Hitbox.cpp for rtype in /home/rochon_k/rendu/rtype/server/src
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:44:52 2016 kevin rochon
// Last update Mon Dec 19 17:10:11 2016 kevin rochon
//

#include "Hitbox.hh"

Hitbox::Hitbox(const int id, const int size) : AComponent(id), _size(size)
{

}

Hitbox::~Hitbox()
{

}

std::pair<int, int>	Hitbox::getPos() const
{
  return (this->_pos);
}

int			Hitbox::getSize() const
{
  return (this->_size);
}

void			Hitbox::setPos(int x, int y)
{
  std::pair <int, int>	pos(x, y);

  this->_pos = pos;
}

void			Hitbox::setSize(int size)
{
  this->_size = size;
}
