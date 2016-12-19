//
// LevelMappingObject.cpp for RType in /home/touzet_t/epitech/cpp/tests/levelsTEST
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Fri Dec 16 17:10:14 2016 Theo TOUZET
// Last update Fri Dec 16 21:02:02 2016 Theo TOUZET
//

#include "LevelMappingObject.hh"

LevelMapping::Object::Object(const LevelMapping::mapCode &code, const LevelMapping::Pair &position, const LevelMapping::Pair vector,
			     const LevelMapping::StringData &name, const LevelMapping::StringData &ai) :
  code(code), position(position), vector(vector), name(name), ai(ai)
{
}

LevelMapping::Object::~Object()
{
}

LevelMapping::Object	&LevelMapping::Object::operator=(LevelMapping::Object const &obj)
{
  code = obj.code;
  position = obj.position;
  vector = obj.vector;
  name = obj.name;
  ai = obj.ai;
  return (*this);
}

bool	LevelMapping::Object::operator==(LevelMapping::Object const &obj) const
{
  if (code != obj.code)
    return (false);
  if (code == LevelMapping::mapCode::Object || code == LevelMapping::mapCode::MovingObject)
    {
      if (code == LevelMapping::mapCode::MovingObject && vector != obj.vector)
	return (false);
    }
  return (true);
}

bool	LevelMapping::Object::operator<(LevelMapping::Object const &obj) const
{
  return (name.data < obj.name.data);
}

LevelMapping::mapCode	LevelMapping::Object::getCode() const
{
  return (this->code);
}

void	LevelMapping::Object::setCode(const LevelMapping::mapCode &_code)
{
  this->code = _code;
}

LevelMapping::Pair	LevelMapping::Object::getPosition() const
{
  return (this->position);
}

void	LevelMapping::Object::setPosition(const int &x, const int &y)
{
  this->setPair(x, y, this->position);
}

void	LevelMapping::Object::setPosition(const LevelMapping::Pair &pair)
{
  this->position.x = pair.x;
  this->position.y = pair.y;
}

LevelMapping::Pair	LevelMapping::Object::getVector() const
{
  return (this->vector);
}

void	LevelMapping::Object::setVector(const int &x, const int &y)
{
  this->setPair(x, y, this->vector);
}

void	LevelMapping::Object::setVector(const LevelMapping::Pair &pair)
{
  this->vector.x = pair.x;
  this->vector.y = pair.y;
}

std::string	LevelMapping::Object::getName() const
{
  return (this->name.data);
}

LevelMapping::StringData	LevelMapping::Object::getNameStruct() const
{
  return (this->name);
}

void	LevelMapping::Object::setName(const std::string &data)
{
  this->setStringData(data, this->name);
}

void	LevelMapping::Object::setName(const LevelMapping::StringData &data)
{
  this->name = data;
}

std::string	LevelMapping::Object::getAI() const
{
  return (this->ai.data);
}

LevelMapping::StringData	LevelMapping::Object::getAIStruct() const
{
  return (this->ai);
}

void	LevelMapping::Object::setAI(const std::string &data)
{
  this->setStringData(data, this->ai);
}

void	LevelMapping::Object::setAI(const LevelMapping::StringData &data)
{
  this->ai = data;
}

void	LevelMapping::Object::fillObject(const mapCode &_code, const Pair &_position, const Pair &_vector, const std::string &_name, const std::string &_ai)
{
  code = _code;
  position = _position;
  vector = _vector;
  name = _name;
  ai = _ai;
}

void	LevelMapping::Object::setPair(const int &x, const int &y, LevelMapping::Pair &pair)
{
  pair.x = x;
  pair.y = y;
}

void	LevelMapping::Object::setStringData(const std::string &data, LevelMapping::StringData &string)
{
  string.length = data.length();
  string.data = data;
}

std::ostream			&LevelMapping::operator<<(std::ostream &os, const LevelMapping::Object &obj)
{
  const LevelMapping::mapCode	&code = obj.getCode();

  os << "Code: " << code << std::endl;
  os << "Position: " << obj.getPosition() << std::endl;
  if (code == LevelMapping::mapCode::MovingObject)
    os << "Vector: " << obj.getVector() << std::endl;
  os << "Name: " << obj.getNameStruct() << std::endl;
  os << "AI: " << obj.getAIStruct() << std::endl;
  return (os);
}

std::ofstream	&LevelMapping::operator<<(std::ofstream &ofs, const LevelMapping::Object &obj)
{
  short		code = static_cast<short>(obj.getCode());
  char		*pc = reinterpret_cast<char*>(&code);

  ofs.write(pc, sizeof(code));
  if (code == LevelMapping::mapCode::Object || code == LevelMapping::mapCode::MovingObject)
    {
      ofs << obj.getPosition();
      if (code == LevelMapping::mapCode::MovingObject)
	ofs << obj.getVector();
      ofs << obj.getNameStruct();
      ofs << obj.getAIStruct();
    }
  return (ofs);
}

std::fstream	&LevelMapping::operator<<(std::fstream &fs, const LevelMapping::Object &obj)
{
  short		code = static_cast<short>(obj.getCode());
  char		*pc = reinterpret_cast<char*>(&code);

  fs.write(pc, sizeof(code));
  if (code == LevelMapping::mapCode::Object || code == LevelMapping::mapCode::MovingObject)
    {
      fs << obj.getPosition();
      if (code == LevelMapping::mapCode::MovingObject)
	fs << obj.getVector();
      fs << obj.getNameStruct();
      fs << obj.getAIStruct();
    }
  return (fs);
}

std::istream			&LevelMapping::operator>>(std::istream &is, LevelMapping::Object &obj)
{
  short				code = 0;
  unsigned char			*pc = reinterpret_cast<unsigned char*>(&code);
  LevelMapping::Pair		pair(0, 0);
  LevelMapping::StringData	data("");

  for (size_t i = 0; i < sizeof(code); ++i, ++pc)
    {
      if (is.eof())
	{
	  obj.setCode(LevelMapping::mapCode::LevelEnd);
	  return (is);
	}
      is >> *pc;
    }
  obj.setCode(static_cast<LevelMapping::mapCode>(code));
  if ((code == LevelMapping::mapCode::Object || code == LevelMapping::mapCode::MovingObject) && !is.eof())
    {
      is >> pair;
      obj.setPosition(pair);
      if (code == LevelMapping::mapCode::MovingObject)
	{
	  is >> pair;
	  obj.setVector(pair);
	}
      is >> data;
      obj.setName(data);
      data = "";
      is >> data;
      obj.setAI(data);
    }
  return (is);
}
