//
// LevelMapping.cpp for RType in /home/touzet_t/epitech/cpp/tests/levels
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Fri Dec  2 18:20:26 2016 Theo TOUZET
// Last update Fri Dec 16 21:08:49 2016 Theo TOUZET
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
