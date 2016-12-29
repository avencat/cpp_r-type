//
// Level.cpp for rtype in /home/touzet_t/epitech/cpp/tests/levels
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Tue Nov 29 16:27:36 2016 Theo TOUZET
// Last update Tue Nov 29 16:39:42 2016 Theo TOUZET
//

#include "Level.hh"

Level::Level(const std::string &_fileName) :
    fileName(_fileName), file(fileName), timeToWait(0)
{
}

Level::~Level()
{
}

const std::string	&Level::getFileName() const
{
    return (fileName);
}

void                Level::setFileName(const std::string &fname)
{
    fileName = fname;
    if (file)
        file.close();
    file.open(fileName);
}

const std::vector<Object*>   &Level::getObjects() const
{
    return (objects);
}

int   Level::getAvailableID() const
{
    int     id = 0;
    Object  obj;

    obj.setId(id);
    while (std::find_if(objects.begin(), objects.end(), [&obj](const Object *p){ return *p == obj; }) != objects.end())
        obj.setId(++id);
    return (id);
}

Object::Type  Level::ObjectTypeToType(const LevelMapping::Object::ObjectType &_t) const
{
    switch (_t)
    {
        case LevelMapping::Object::ObjectType::PLAYER :
            return (Object::Type::PLAYER);
        case LevelMapping::Object::ObjectType::PLAYERBULLET :
            return (Object::Type::PLAYERBULLET);
        case LevelMapping::Object::ObjectType::ENEMY :
            return (Object::Type::ENEMY);
        case LevelMapping::Object::ObjectType::ENEMYBULLET :
            return (Object::Type::ENEMYBULLET);
        case LevelMapping::Object::ObjectType::OBSTACLE :
            return (Object::Type::OBSTACLE);
        case LevelMapping::Object::ObjectType::POWERUP :
            return (Object::Type::POWERUP);
        default:
            return (Object::Type::NONE);
    }
}

void                        Level::createObject(const LevelMapping::Object &obj)
{
    LevelMapping::mapCode   code = obj.getCode();
    Object                  *_obj = new Object(getAvailableID());
    AComponent              *comp;

    if (code == LevelMapping::mapCode::Object || code == LevelMapping::mapCode::MovingObject)
    {
        _obj->setType(ObjectTypeToType(obj.getObjectType()));
        const std::vector<LevelMapping::Sprite> sprs = obj.getSprites();
        for (std::vector<LevelMapping::Sprite>::const_iterator it = sprs.begin(); it != sprs.end(); ++it)
        {
            comp = new Sprite(it->name.data, it->pos.x, it->pos.y);
            _obj->addComponent(comp);
        }
        const std::vector<LevelMapping::Hitbox> hbxs = obj.getHitboxes();
        for (std::vector<LevelMapping::Hitbox>::const_iterator it = hbxs.begin(); it != hbxs.end(); ++it)
        {
            comp = new Hitbox(it->pos.x, it->pos.y, it->size.x, it->size.y);
            _obj->addComponent(comp);
        }
        _obj->setHp(1);
        if (code == LevelMapping::mapCode::MovingObject)
        {
            const LevelMapping::Pair  p = obj.getVector();
            _obj->setMovement(p.x, p.y);
        }
        objects.push_back(_obj);
    }
}

void                                  Level::deleteObject(const int id)
{
    Object                            obj(id);
    std::vector<Object*>::iterator    it;

    if ((it = std::find_if(objects.begin(), objects.end(), [&obj](const Object *p){ return *p == obj; })) != objects.end())
    {
        delete *it;
        objects.erase(it);
    }
}

void                Level::updateObject()
{

}

bool		Level::readFile()
{
    return (false);
}

bool		Level::readFile(const std::string &fname)
{
    fileName = fname;
    if (file.is_open())
        file.close();
    file.open(fname);
    return (false);
}

void        Level::loopGame()
{
    readFile();
}
