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

Sprite::Sprite(const std::string &name, const int pos_x, const int pos_y) :
        AComponent(AComponent::SPRITE), _name(name), _pos(pos_x, pos_y)
{
}

Sprite::~Sprite()
{
}

const std::pair<int, int>	&Sprite::getPos() const
{
  return (this->_pos);
}

const std::string		&Sprite::getName() const
{
  return (this->_name);
}

void			Sprite::setPos(const int x , const int y)
{
    std::pair <int, int> pos(x, y);

    this->_pos = pos;
}

void			Sprite::setPos(const std::pair<int, int> &pos)
{
    this->_pos = pos;
}

void			Sprite::setName(const std::string &name)
{
  this->_name = name;
}

std::ostream    &operator<<(std::ostream &os, const Sprite &spr)
{
  std::pair<int, int> p = spr.getPos();

  os << "Type: Sprite" << std::endl;
  os << "Name: " << spr.getName() << std::endl;
  os << "Position (x;y): " << p.first << ";" << p.second << std::endl;
  return (os);
}