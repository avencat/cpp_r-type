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

Hitbox::Hitbox(const int pos_x, const int pos_y, const int size_x, const int size_y) :
        AComponent(AComponent::HITBOX), _pos(pos_x, pos_y), _size(size_x, size_y)
{
}

Hitbox::~Hitbox()
{
}

const std::pair<int, int>	&Hitbox::getPos() const
{
  return (this->_pos);
}

const std::pair<int, int>	&Hitbox::getSize() const
{
  return (this->_size);
}

void			Hitbox::setPos(int x, int y)
{
  std::pair <int, int>	pos(x, y);

  this->_pos = pos;
}

void			Hitbox::setSize(const int x, const int y)
{
  this->_size = std::pair<int, int>(x, y);
}

std::ostream    &operator<<(std::ostream &os, const Hitbox &hbx)
{
  std::pair<int, int> p = hbx.getPos();

  os << "Type: Hitbox" << std::endl;
  os << "Position (x;y): " << p.first << ";" << p.second << std::endl;
  p = hbx.getSize();
  os << "Size (x;y): " << p.first << ";" << p.second << std::endl;
  return (os);
}
