//
// Level.hh for rtype in /home/touzet_t/epitech/cpp/tests/levels
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Tue Nov 29 16:27:45 2016 Theo TOUZET
// Last update Tue Nov 29 16:39:49 2016 Theo TOUZET
//

#ifndef LEVEL_HH_
# define LEVEL_HH_

# include <chrono>
# include <fstream>
# include <map>
# include <string>
# include <vector>
# include "Object.hh"
# include "LevelMappingObject.hh"
# include "LevelMappingMap.hh"

class	Level
{
private:
    struct Collider
    {
        Collider(Hitbox &_hb, Object &_obj) : hb(_hb), obj(_obj) {}
        Hitbox  &hb;
        Object  &obj;
    };

public:
  Level(const std::string &_fileName = "stage1.lvl", const bool &forceTrunc = false);
  ~Level();

  const std::string	&getFileName() const;
  void		setFileName(const std::string &fname);
  const std::vector<Object*>   &getObjects() const;
  Object::Type ObjectTypeToType(const LevelMapping::Object::ObjectType &_t) const;

  void    createObject(const LevelMapping::Object &obj);
  int     getAvailableID() const;
  void    deleteObject(const int id);
  bool    updateObject(const Object &obj, const std::pair<int, int> &movement = std::pair<int, int>(0, 0));

  bool      isWaitOver() const;
  bool		readFile();
  bool		readFile(const std::string &fname);

  void      playerCollision(Object &player, Object &coll) const;
  void      enemyCollision(Object &enemy, Object &coll) const;
  void      updateObjectsOnCollision(const std::vector<std::pair<Object&, Object&>> &coll);
  void      checkCollisions();
  void      checkFire(Object &obj);
  bool      checkAlive();
  void      initGame(const int &players);
  bool      loopGame();

  void      dump() const;

private:
  void      gatherHitboxes();

private:
  std::string	            fileName;
  LevelMapping::Map         fileMap;
  std::streampos            checkpoint;
  double                    timeToWait;
  std::vector<Object*>      objects;
  std::vector<Object*>      players;
  std::vector<Collider>     colliders;
  std::chrono::steady_clock::time_point waitingSince;
  std::chrono::steady_clock::time_point lastLoop;
};

#endif /* !LEVEL_HH_ */
