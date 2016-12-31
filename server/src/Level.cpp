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
    fileName(_fileName), fileMap(fileName), timeToWait(0)
{
}

Level::~Level()
{
    while (objects.size() > 0)
    {
        delete objects[0];
        objects.erase(objects.begin());
    }
    if (fileMap.isOpen())
        fileMap.close();
}

const std::string	&Level::getFileName() const
{
    return (fileName);
}

void                Level::setFileName(const std::string &fname)
{
    fileName = fname;
    if (fileMap.isOpen())
        fileMap.close();
    fileMap.open(fileName);
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
        // TODO send object created to clients and specs
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

bool                Level::updateObject(const Object &obj, const std::pair<int, int> &movement)
{
    std::vector<Object*>::iterator    it;
    std::pair<int, int> p;

    if ((it = std::find_if(objects.begin(), objects.end(), [&obj](const Object *p){ return *p == obj; })) != objects.end())
    {
        p = obj.getMovement();
        (*it)->setMovement(p.first, p.second);
        (*it)->moveComponents(movement);
        (*it)->setHp(obj.getHp());
        return (true);
    }
    return (false);
}

bool            Level::isWaitOver() const
{
    std::chrono::steady_clock::time_point   tp = std::chrono::steady_clock::now();
    std::chrono::duration<double>           time_span = std::chrono::duration_cast<std::chrono::duration<double>>(tp - waitingSince);

    return (time_span.count() >= timeToWait);
}

bool		                Level::readFile()
{
    LevelMapping::Object    obj;
    bool                    read = true;

    if (fileMap.isOpen())
    {
        if (!isWaitOver())
            return (true);
        while (read && fileMap.isOpen() && !fileMap.eof())
        {
            fileMap.getNextObject(obj);
            switch (obj.getCode())
            {
                case LevelMapping::mapCode::Object :
                    createObject(obj);
                    break;
                case LevelMapping::mapCode::MovingObject :
                    createObject(obj);
                    break;
                case LevelMapping::mapCode::Checkpoint :
                    checkpoint = fileMap.getStreamPosition();
                    break;
                case LevelMapping::mapCode::LevelEnd :
                    read = false;
                    break;
                case LevelMapping::mapCode::Wait :
                    read = false;
                    timeToWait = static_cast<double>(obj.getWaitTime()) / 1000;
                    waitingSince = std::chrono::steady_clock::now();
                    break;
                default:
                    break;
            }
        }
        return (fileMap.isOpen() && !fileMap.eof());
    }
    return (false);
}

bool		Level::readFile(const std::string &fname)
{
    fileName = fname;
    if (fileMap.isOpen())
        fileMap.close();
    fileMap.open(fname);
    checkpoint = fileMap.getStreamPosition();
    return (readFile());
}

void        Level::gatherHitboxes()
{
    std::vector<AComponent*>    comps;
    Level::Collider             coll;

    colliders.clear();
    for (std::vector<Object*>::iterator obj = objects.begin(); obj != objects.end(); ++obj)
    {
        coll.obj = *(*obj);
        comps.clear();
        comps = (*obj)->getComponents();
        for (std::vector<AComponent*>::iterator comp = comps.begin(); comp != comps.end(); ++comp)
        {
            if ((*comp)->getId() == AComponent::Type::HITBOX)
            {
                coll.hb = *(dynamic_cast<Hitbox *>(*comp));
                colliders.push_back(coll);
            }
        }
    }
}

void            Level::playerCollision(Object &player, Object &coll) const
{
    switch (coll.getType())
    {
        case Object::Type::PLAYER | Object::Type::PLAYERBULLET :
            break;
        case Object::Type::ENEMY | Object::Type::ENEMYBULLET :
            player.setHp(0);
            coll.setHp(coll.getHp() - 1);
            break;
        case Object::Type::OBSTACLE :
            player.setHp(0);
            break;
        default:
            break;
    }
}

void            Level::enemyCollision(Object &enemy, Object &coll) const
{
    switch (coll.getType())
    {
        case Object::Type::PLAYER | Object::Type::PLAYERBULLET :
            enemy.setHp(enemy.getHp() - 1);
            coll.setHp(0);
            break;
        case Object::Type::ENEMY | Object::Type::ENEMYBULLET :
            break;
        case Object::Type::OBSTACLE :
            enemy.setHp(0);
            break;
        default:
            break;
    }
}

void                Level::updateObjectsOnCollision(const std::vector<std::pair<Object&, Object&>> &coll)
{
    Object::Type    tp;

    for (std::vector<std::pair<Object&, Object&>>::const_iterator it = coll.begin(); it != coll.end(); ++it)
    {
        tp = it->first.getType();
        switch (tp)
        {
            case Object::Type::PLAYER | Object::Type::PLAYERBULLET :
                playerCollision(it->first, it->second);
                break;
            case Object::Type::ENEMY | Object::Type::ENEMYBULLET :
                enemyCollision(it->first, it->second);
                break;
            default:
                tp = it->second.getType();
        }
    }
}

void                            Level::checkCollisions()
{
    std::vector<std::pair<Object&, Object&>>  coll;

    gatherHitboxes();
    for (std::vector<Collider>::iterator it1 = colliders.begin(); it1 != colliders.end(); ++it1)
      for (std::vector<Collider>::iterator it2 = colliders.begin(); it2 != colliders.end(); ++it2)
        if (it1->hb.doesCollide(it2->hb) &&
            std::find(coll.begin(), coll.end(), std::pair<Object&, Object&>(it2->obj, it1->obj)) == coll.end() &&
            std::find(coll.begin(), coll.end(), std::pair<Object&, Object&>(it1->obj, it2->obj)) == coll.end())
          coll.push_back(std::pair<Object&, Object&>(it1->obj, it2->obj));
    updateObjectsOnCollision(coll);
}

bool    Level::checkAlive()
{
    for (std::vector<Object*>::iterator it = objects.begin(); it != objects.end();)
    {
        if ((*it)->getHp() <= 0)
        {
            // TODO send Object destroyed
            deleteObject((*it)->getId());
            it = objects.begin();
        }
        else
            ++it;
    }
    for (std::vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it)
    {
        return (true);
    }
    return (false);
}

bool        Level::loopGame()
{
    readFile();
    for (std::vector<Object*>::iterator obj = objects.begin(); obj != objects.end(); ++obj)
        (*obj)->moveComponents();
    checkCollisions();
    return (checkAlive());
}

void                            Level::dump() const
{
    Object::Type                type;
    std::map<Object::Type, int> map;

    std::cout << "Dumping all objects in Level:" << std::endl;
    for (std::vector<Object*>::const_iterator it = objects.begin(); it != objects.end(); ++it)
    {
        std::cout << *(*it) << std::endl;
        type = (*it)->getType();
        if (map.find(type) != map.end())
            map[type] += 1;
        else
            map.insert(std::pair<Object::Type, int>(type, 1));
    }
    std::cout << "Total number of Objects: " << objects.size() << "." << std::endl;
    std::cout << "Detail:" << std::endl;
    for (std::map<Object::Type, int>::const_iterator it = map.begin(); it != map.end(); ++it)
        std::cout << "\t- " << it->first << ": " << it->second << " occurrence" << (it->second > 1 ? "s" : "") << std::endl;
}