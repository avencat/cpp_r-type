//
// LevelMapping.cpp for RType in /home/touzet_t/epitech/cpp/tests/levels
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Fri Dec  2 18:20:26 2016 Theo TOUZET
// Last update Mon Dec 19 16:12:17 2016 Theo TOUZET
//

#include "LevelMapping.hh"

// mapCode

bool	LevelMapping::operator==(const short &a, const LevelMapping::mapCode &b)
{
  return (static_cast<short>(b) == a);
}

bool	LevelMapping::operator==(const LevelMapping::mapCode &a, const short &b)
{
    return (static_cast<short>(a) == b);
}

std::ofstream	&LevelMapping::operator<<(std::ofstream &ofs, const LevelMapping::mapCode &code)
{
  ofs << static_cast<short>(code);
  return (ofs);
}

std::fstream	&LevelMapping::operator<<(std::fstream &fs, const LevelMapping::mapCode &code)
{
  fs << static_cast<short>(code);
  return (fs);
}

std::ostream	&LevelMapping::operator<<(std::ostream &os, const LevelMapping::mapCode &code)
{
  os << static_cast<short>(code);
  return (os);
}

// Pair
LevelMapping::Pair::Pair() :
  x(0), y(0)
{
}

LevelMapping::Pair::Pair(int _x, int _y) :
  x(_x), y(_y)
{
}

LevelMapping::Pair	&LevelMapping::Pair::operator=(const LevelMapping::Pair &p)
{
  x = p.x;
  y = p.y;
  return (*this);
}

bool	LevelMapping::Pair::operator==(const LevelMapping::Pair &p) const
{
  return (p.x == x && p.y == y);
}

bool	LevelMapping::Pair::operator<(const LevelMapping::Pair &p) const
{
  return (sqrt(pow(x, 2) + pow(y, 2)) < sqrt(pow(p.x, 2) + pow(p.y, 2)));
}

std::ofstream		&LevelMapping::operator<<(std::ofstream &ofs, const LevelMapping::Pair &pair)
{
  LevelMapping::Pair	p = pair;
  char			*pc = reinterpret_cast<char*>(&(p.x));

  ofs.write(pc, sizeof(p.x));
  pc = reinterpret_cast<char*>(&(p.y));
  ofs.write(pc, sizeof(p.x));
  return (ofs);
}

std::fstream		&LevelMapping::operator<<(std::fstream &fs, const LevelMapping::Pair &pair)
{
  LevelMapping::Pair	p = pair;
  char			*pc = reinterpret_cast<char*>(&(p.x));

  fs.write(pc, sizeof(p.x));
  pc = reinterpret_cast<char*>(&(p.y));
  fs.write(pc, sizeof(p.x));
  return (fs);
}

std::ostream	&LevelMapping::operator<<(std::ostream &os, const LevelMapping::Pair &pair)
{
  os << pair.x << ";" << pair.y;
  return (os);
}

std::istream	&LevelMapping::operator>>(std::istream &is, LevelMapping::Pair &p)
{
  char		*pc = reinterpret_cast<char*>(&(p.x));

  is.read(pc, sizeof(p.x));
  pc = reinterpret_cast<char*>(&(p.y));
  is.read(pc, sizeof(p.y));
  return (is);
}

// StringData
LevelMapping::StringData::StringData()
{
  length = 0;
  data = "";
}

LevelMapping::StringData::StringData(const std::string &str)
{
  length = str.length();
  data = str;
}

LevelMapping::StringData	&LevelMapping::StringData::operator=(const LevelMapping::StringData &str)
{
  data = str.data;
  length = str.length;
  return (*this);
}

LevelMapping::StringData	&LevelMapping::StringData::operator=(const std::string &str)
{
  data = str;
  length = str.length();
  return (*this);
}

bool	LevelMapping::StringData::operator==(const LevelMapping::StringData &str) const
{
  return (data == str.data);
}

bool	LevelMapping::StringData::operator<(const LevelMapping::StringData &str) const
{
  return (data < str.data);
}

bool	LevelMapping::StringData::operator==(const std::string &str) const
{
  return (data == str);
}

bool	LevelMapping::StringData::operator<(const std::string &str) const
{
  return (data < str);
}

std::ofstream			&LevelMapping::operator<<(std::ofstream &ofs, const LevelMapping::StringData &strdata)
{
  LevelMapping::StringData	data = strdata;
  char				*length = reinterpret_cast<char*>(&(data.length));

  ofs.write(length, sizeof(data.length));
  ofs.write(&data.data[0], data.length);
  return (ofs);
}

std::fstream			&LevelMapping::operator<<(std::fstream &fs, const LevelMapping::StringData &strdata)
{
  LevelMapping::StringData	data = strdata;
  char				*length = reinterpret_cast<char*>(&(data.length));

  fs.write(length, sizeof(data.length));
  fs.write(&data.data[0], data.length);
  return (fs);
}

std::ostream	&LevelMapping::operator<<(std::ostream &os, const LevelMapping::StringData &str)
{
  os << str.data;
  return (os);
}

std::istream	&LevelMapping::operator>>(std::istream &is, LevelMapping::StringData &data)
{
  char		*length = reinterpret_cast<char*>(&(data.length));

  is.read(length, sizeof(data.length));
  data.data.resize(data.length);
  is.read(&data.data[0], data.length);

  return (is);
}

// Sprite
LevelMapping::Sprite::Sprite()
{
}

LevelMapping::Sprite::Sprite(const LevelMapping::StringData &_name, const LevelMapping::Pair &_pos)
{
  name = _name;
  pos = _pos;
}

std::ofstream	&LevelMapping::operator<<(std::ofstream &ofs, const LevelMapping::Sprite &spr)
{
  return (ofs << spr.name << spr.pos);
}

std::fstream	&LevelMapping::operator<<(std::fstream &fs, const LevelMapping::Sprite &spr)
{
  return (fs << spr.name << spr.pos);
}

std::ostream	&LevelMapping::operator<<(std::ostream &os, const LevelMapping::Sprite &spr)
{
  os << "Sprite name: " << spr.name << std::endl;
  os << "Position: " << spr.pos.x << ";" << spr.pos.y << std::endl;
  return (os);
}

std::istream	&LevelMapping::operator>>(std::istream &is, LevelMapping::Sprite &spr)
{
  return (is >> spr.name >> spr.pos);
}

bool    LevelMapping::Sprite::operator==(const LevelMapping::Sprite &spr) const
{
  return (spr.name == name && spr.pos == pos);
}

// Hitbox
LevelMapping::Hitbox::Hitbox()
{
}

LevelMapping::Hitbox::Hitbox(const LevelMapping::Pair &_pos, const LevelMapping::Pair &_size)
{
  pos = _pos;
  size = _size;
}

LevelMapping::Hitbox::Hitbox(const int posx, const int posy, const int sizex, const int sizey)
{
  pos = LevelMapping::Pair(posx, posy);
  size = LevelMapping::Pair(sizex, sizey);
}

std::ofstream	&LevelMapping::operator<<(std::ofstream &ofs, const LevelMapping::Hitbox &hb)
{
  return (ofs << hb.pos << hb.size);
}

std::fstream	&LevelMapping::operator<<(std::fstream &fs, const LevelMapping::Hitbox &hb)
{
  return (fs << hb.pos << hb.size);
}

std::ostream	&LevelMapping::operator<<(std::ostream &os, const LevelMapping::Hitbox &hb)
{
  os << "Hitbox position: " << hb.pos.x << ";" << hb.pos.y << std::endl;
  os << "Size: " << hb.size.x << ";" << hb.size.y << std::endl;
  return (os);
}

std::istream	&LevelMapping::operator>>(std::istream &is, LevelMapping::Hitbox &hb)
{
  return (is >> hb.pos >> hb.size);
}

bool    LevelMapping::Hitbox::operator==(const LevelMapping::Hitbox &hb) const
{
  return (pos == hb.pos && size == hb.size);
}
