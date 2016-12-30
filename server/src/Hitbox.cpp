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

void			Hitbox::setPos(const int x, const int y)
{
    std::pair <int, int>	pos(x, y);

    this->_pos = pos;
}

void			Hitbox::setPos(const std::pair<int, int> &pos)
{
    this->_pos = pos;
}

void			Hitbox::setSize(const int x, const int y)
{
    this->_size = std::pair<int, int>(x, y);
}

void			Hitbox::setSize(const std::pair<int, int> &size)
{
    this->_size = size;
}

bool                    Hitbox::doesCollide(const Hitbox &hb) const
{
    std::pair<int, int> pos = hb.getPos();
    std::pair<int, int> size = hb.getSize();

    if ((pos.first < _pos.first && _pos.first < pos.first + size.first) &&
        (pos.second < _pos.second && _pos.second < pos.second + size.second))
        return (true);
    else if ((pos.first < _pos.first + _size.first && _pos.first + _size.first < pos.first + size.first) &&
             (pos.second < _pos.second + _size.second && _pos.second + _size.second < pos.second + size.second))
        return (true);
    return ((_pos.first < pos.first && pos.first + size.first < _pos.first + _size.first) &&
            (_pos.second < pos.second && pos.second + size.second < _pos.second + _size.second));
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
