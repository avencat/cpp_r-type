//
// LevelMappingObject.cpp for RType in /home/touzet_t/epitech/cpp/tests/levelsTEST
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Fri Dec 16 17:10:14 2016 Theo TOUZET
// Last update Mon Dec 19 16:47:53 2016 Theo TOUZET
//

#include "LevelMappingObject.hh"

LevelMapping::Object::Object(const mapCode &code, const ObjectType &type, const std::vector<Sprite> &_sprites,
                             const std::vector<Hitbox> &_hitboxes, const Pair vector, const StringData &ai, const int _waitTime) :
  code(code), type(type), sprites(_sprites), hitboxes(_hitboxes), vector(vector), ai(ai), waitTime(_waitTime)
{
}

LevelMapping::Object::~Object()
{
}

LevelMapping::Object	&LevelMapping::Object::operator=(LevelMapping::Object const &obj)
{
  code = obj.code;
  sprites = obj.sprites;
  hitboxes = obj.hitboxes;
  vector = obj.vector;
  ai = obj.ai;
  return (*this);
}

bool	LevelMapping::Object::operator==(LevelMapping::Object const &obj) const
{
  if (code != obj.code)
    return (false);
  else if ((code == LevelMapping::mapCode::Object || code == LevelMapping::mapCode::MovingObject) &&
          code == LevelMapping::mapCode::MovingObject && vector != obj.vector)
	return (false);
  return (true);
}

bool	LevelMapping::Object::operator<(LevelMapping::Object const &obj) const
{
  return (code < obj.code);
}

const LevelMapping::mapCode	&LevelMapping::Object::getCode() const
{
  return (this->code);
}

void	LevelMapping::Object::setCode(const LevelMapping::mapCode &_code)
{
  this->code = _code;
}

const LevelMapping::Object::ObjectType  &LevelMapping::Object::getObjectType() const
{
    return (type);
}

void                                    LevelMapping::Object::setObjectType(const LevelMapping::Object::ObjectType &_t)
{
    type = _t;
}

int                                     LevelMapping::Object::getWaitTime() const
{
    return (waitTime);
}

void                                    LevelMapping::Object::setWaitTime(const int _wait)
{
    waitTime = _wait;
}

const std::vector<LevelMapping::Sprite>	&LevelMapping::Object::getSprites() const
{
  return (this->sprites);
}

void	                LevelMapping::Object::addSprite(const std::string &name, const int posx, const int posy)
{
  this->sprites.push_back(LevelMapping::Sprite(name, LevelMapping::Pair(posx, posy)));
}

void	        LevelMapping::Object::addSprite(const std::string &name, const Pair &pos)
{
    this->sprites.push_back(LevelMapping::Sprite(name, pos));
}

void		LevelMapping::Object::addSprite(const LevelMapping::Sprite &spr)
{
    this->sprites.push_back(spr);
}

void		LevelMapping::Object::removeSprite(const std::string &name)
{
    for (std::vector<Sprite>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it)
        if ((*it).name == name)
        {
            this->sprites.erase(it);
            it = this->sprites.begin();
        }
}

void		LevelMapping::Object::removeSprite(const Pair &pos)
{
    for (std::vector<Sprite>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it)
        if ((*it).pos == pos)
        {
            this->sprites.erase(it);
            it = this->sprites.begin();
        }
}

void		LevelMapping::Object::removeSprite(const int x, const int y)
{
    LevelMapping::Pair p(x, y);

    for (std::vector<Sprite>::iterator it = this->sprites.begin(); it != this->sprites.end(); ++it)
        if ((*it).pos == p)
        {
            this->sprites.erase(it);
            it = this->sprites.begin();
        }
}

void		LevelMapping::Object::removeSprite(const LevelMapping::Sprite &spr)
{
    std::vector<LevelMapping::Sprite>::iterator it;

    while ((it = std::find(sprites.begin(), sprites.end(), spr)) != sprites.end())
        sprites.erase(it);
}

void    LevelMapping::Object::clearSprites()
{
    sprites.clear();
}

const std::vector<LevelMapping::Hitbox>	&LevelMapping::Object::getHitboxes() const
{
    return (this->hitboxes);
}

void	        LevelMapping::Object::addHitbox(const int posx, const int posy, const int sizex, const int sizey)
{
    hitboxes.push_back(LevelMapping::Hitbox(LevelMapping::Pair(posx, posy), LevelMapping::Pair(sizex, sizey)));
}

void	        LevelMapping::Object::addHitbox(const Pair &pos, const Pair &size)
{
    hitboxes.push_back(LevelMapping::Hitbox(pos, size));
}

void		LevelMapping::Object::addHitbox(const LevelMapping::Hitbox &hb)
{
    hitboxes.push_back(hb);
}

void		LevelMapping::Object::removeHitbox(const int posx, const int posy, const int sizex, const int sizey)
{
    LevelMapping::Hitbox    hb(LevelMapping::Pair(posx, posy), LevelMapping::Pair(sizex, sizey));
    std::vector<Hitbox>::iterator it;

    while ((it = std::find(hitboxes.begin(), hitboxes.end(), hb)) != hitboxes.end())
        hitboxes.erase(it);
}

void		LevelMapping::Object::removeHitbox(const Pair &pos, const Pair &size)
{
    LevelMapping::Hitbox    hb(pos, size);
    std::vector<Hitbox>::iterator it;

    while ((it = std::find(hitboxes.begin(), hitboxes.end(), hb)) != hitboxes.end())
        hitboxes.erase(it);
}

void		LevelMapping::Object::removeHitbox(const LevelMapping::Hitbox &hb)
{
    std::vector<Hitbox>::iterator   it;

    while ((it = std::find(hitboxes.begin(), hitboxes.end(), hb)) != hitboxes.end())
        hitboxes.erase(it);
}

void    LevelMapping::Object::clearHitboxes()
{
    hitboxes.clear();
}

const LevelMapping::Pair	&LevelMapping::Object::getVector() const
{
    return (vector);
}

void		LevelMapping::Object::setVector(const int x, const int y)
{
    vector.x = x;
    vector.y = y;
}

void		LevelMapping::Object::setVector(const LevelMapping::Pair &pair)
{
    vector = pair;
}

std::string	LevelMapping::Object::getAI() const
{
  return (this->ai.data);
}

const LevelMapping::StringData	&LevelMapping::Object::getAIStruct() const
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

void	LevelMapping::Object::fillObject(const mapCode &_code, const std::vector<Sprite> &_sprites, const std::vector<Hitbox> &_hitboxes, const Pair &_vector, const std::string &_ai)
{
  code = _code;
  sprites = _sprites;
  hitboxes = _hitboxes;
  vector = _vector;
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

std::ostream	                        &LevelMapping::operator<<(std::ostream &os, const LevelMapping::Object::ObjectType &type)
{
    LevelMapping::Object::ObjectType    _t = type;

    switch (_t)
    {
        case LevelMapping::Object::ObjectType::PLAYER :
            os << "Player";
            break;
        case LevelMapping::Object::ObjectType::ENEMY :
            os << "Enemy";
            break;
        case LevelMapping::Object::ObjectType::OBSTACLE :
            os << "Obstacle";
            break;
        case LevelMapping::Object::ObjectType::ENEMYBULLET :
            os << "Enemy bullet";
            break;
        case LevelMapping::Object::ObjectType::PLAYERBULLET :
            os << "Player bullet";
            break;
        case LevelMapping::Object::ObjectType::POWERUP :
            os << "Power-Up";
            break;
        case LevelMapping::Object::ObjectType::NONE :
            os << "None";
            break;
        default:
            os << "Invalid type";
            break;
    }
    return (os);
}

std::ofstream	&LevelMapping::operator<<(std::ofstream &ofs, const LevelMapping::Object::ObjectType &type)
{
    LevelMapping::Object::ObjectType    _t = type;
    char                                *t = reinterpret_cast<char*>(&_t);

    ofs.write(t, sizeof(_t));
    return (ofs);
}

std::fstream	&LevelMapping::operator<<(std::fstream &fs, const LevelMapping::Object::ObjectType &type)
{
    LevelMapping::Object::ObjectType    _t = type;
    char                                *t = reinterpret_cast<char*>(&_t);

    fs.write(t, sizeof(_t));
    return (fs);
}

std::istream	&LevelMapping::operator>>(std::istream &is, LevelMapping::Object::ObjectType &type)
{
    LevelMapping::Object::ObjectType    _t = type;
    char                                *t = reinterpret_cast<char*>(&_t);

    is.read(t, sizeof(_t));
    return (is);
}

std::ostream			&LevelMapping::operator<<(std::ostream &os, const LevelMapping::Object &obj)
{
  const LevelMapping::mapCode	&code = obj.getCode();
  const std::vector<LevelMapping::Sprite> &sprites = obj.getSprites();
  const std::vector<LevelMapping::Hitbox> &hitboxes = obj.getHitboxes();

  os << "Code: " << code << std::endl;
  if (code == LevelMapping::mapCode::Object || code == LevelMapping::mapCode::MovingObject) {
      os << "Type: " << obj.getObjectType() << std::endl;
      if (sprites.size() > 0) {
          os << "Sprite" << (sprites.size() == 1 ? "" : "s") << ": " << std::endl;
          for (std::vector<LevelMapping::Sprite>::const_iterator it = sprites.begin(); it != sprites.end(); ++it)
              os << "\t- " << it->name << ": " << it->pos.x << ";" << it->pos.y << std::endl;
      }
      if (hitboxes.size() > 0) {
          os << "Hitbox" << (hitboxes.size() == 1 ? "" : "es") << ": " << std::endl;
          for (std::vector<LevelMapping::Hitbox>::const_iterator it = hitboxes.begin(); it != hitboxes.end(); ++it)
              os << "\t- " << it->pos.x << ";" << it->pos.y << " | " << it->size.x << ";" << it->size.y << std::endl;
      }
      if (code == LevelMapping::mapCode::MovingObject)
          os << "Vector: " << obj.getVector() << std::endl;
  }
  else if (code == LevelMapping::mapCode::Wait)
    os << "Time to wait (in ms): " << obj.getWaitTime() << std::endl;
  os << "AI: " << obj.getAIStruct() << std::endl;
  return (os);
}

std::ofstream	&LevelMapping::operator<<(std::ofstream &ofs, const LevelMapping::Object &obj)
{
  short		code = static_cast<short>(obj.getCode());
  int waitTime = obj.getWaitTime();
  char		*pc = reinterpret_cast<char*>(&code);
  LevelMapping::Object::ObjectType type = obj.getObjectType();

    ofs.write(pc, sizeof(code));
  if (code == LevelMapping::mapCode::Object || code == LevelMapping::mapCode::MovingObject)
    {
        ofs.write(reinterpret_cast<char*>(&type), sizeof(type));
        const std::vector<LevelMapping::Sprite> sprites = obj.getSprites();
        const std::vector<LevelMapping::Hitbox> hitboxes = obj.getHitboxes();
        unsigned long   sz = sprites.size();

        ofs.write(reinterpret_cast<char*>(&sz), sizeof(sz));
        if (sz > 0)
            for (std::vector<LevelMapping::Sprite>::const_iterator it = sprites.begin(); it != sprites.end(); ++it)
                ofs << *it;
        sz = hitboxes.size();
        ofs.write(reinterpret_cast<char*>(&sz), sizeof(sz));
        if (sz > 0)
            for (std::vector<LevelMapping::Hitbox>::const_iterator it = hitboxes.begin(); it != hitboxes.end(); ++it)
                ofs << *it;
        if (code == LevelMapping::mapCode::MovingObject)
    	    ofs << obj.getVector();
        ofs << obj.getAIStruct();
    }
  else if (code == LevelMapping::mapCode::Wait)
      ofs.write(reinterpret_cast<char*>(&waitTime), sizeof(waitTime));
  return (ofs);
}

std::fstream	&LevelMapping::operator<<(std::fstream &fs, const LevelMapping::Object &obj)
{
  short		code = static_cast<short>(obj.getCode());
  int waitTime = obj.getWaitTime();
  char		*pc = reinterpret_cast<char*>(&code);
  LevelMapping::Object::ObjectType type = obj.getObjectType();

  fs.write(pc, sizeof(code));
  if (code == LevelMapping::mapCode::Object || code == LevelMapping::mapCode::MovingObject)
    {
        const std::vector<LevelMapping::Sprite> sprites = obj.getSprites();
        const std::vector<LevelMapping::Hitbox> hitboxes = obj.getHitboxes();
        unsigned long sz = sprites.size();

        fs.write(reinterpret_cast<char*>(&type), sizeof(type));
        fs.write(reinterpret_cast<char*>(&sz), sizeof(sz));
        if (sz > 0)
            for (std::vector<LevelMapping::Sprite>::const_iterator it = sprites.begin(); it != sprites.end(); ++it)
                fs << *it;
        sz = hitboxes.size();
        fs.write(reinterpret_cast<char*>(&sz), sizeof(sz));
        if (sz > 0)
            for (std::vector<LevelMapping::Hitbox>::const_iterator it = hitboxes.begin(); it != hitboxes.end(); ++it)
                fs << *it;
        if (code == LevelMapping::mapCode::MovingObject)
            fs << obj.getVector();
        fs << obj.getAIStruct();
    }
  else if (code == LevelMapping::mapCode::Wait)
      fs.write(reinterpret_cast<char*>(&waitTime), sizeof(waitTime));
  return (fs);
}

std::istream			&LevelMapping::operator>>(std::istream &is, LevelMapping::Object &obj)
{
  short				    code = 0;
  unsigned char			*pc = reinterpret_cast<unsigned char*>(&code);
  LevelMapping::Pair		pair(0, 0);
  LevelMapping::StringData	data("");
  unsigned long        vecSize = 0;
  char                  *pv = reinterpret_cast<char*>(&vecSize);
  LevelMapping::Object::ObjectType type;

  obj.clearSprites();
  obj.clearHitboxes();
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
        is.read(reinterpret_cast<char*>(&type), sizeof(type));
        obj.setObjectType(type);
        is.read(pv, sizeof(vecSize));
        for (unsigned int i = 0; i < vecSize; ++i)
        {
            is >> data;
            is >> pair;
            obj.addSprite(data.data, pair);
            data = "";
        }
        pv = reinterpret_cast<char*>(&vecSize);
        is.read(pv, sizeof(vecSize));
        LevelMapping::Pair  pair2;
        for (unsigned int i = 0; i < vecSize; ++i)
        {
            is >> pair;
            is >> pair2;
            obj.addHitbox(pair, pair2);
        }
      if (code == LevelMapping::mapCode::MovingObject)
    	{
	      is >> pair;
    	  obj.setVector(pair);
    	}
      is >> data;
      obj.setAI(data);
    }
  else if (code == LevelMapping::mapCode::Wait)
  {
      int waitTime = 0;
      is.read(reinterpret_cast<char*>(&waitTime), sizeof(waitTime));
      obj.setWaitTime(waitTime);
  }
  return (is);
}
