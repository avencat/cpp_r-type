//
// Object.hh for rtype in /home/rochon_k/rendu/rtype/server/include
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:41:55 2016 kevin rochon
// Last update Mon Dec 19 18:49:34 2016 kevin rochon
//

#ifndef OBJECT_HH_
# define OBJECT_HH_

# include <algorithm>
# include <exception>
# include <iostream>
# include <string>
# include <typeinfo>
# include <utility>
# include <vector>
# include "AComponent.hh"
# include "Relationnals.hpp"

class		Object: public Relationnals<Object>
{
 public:
  enum		Type
    {
      PLAYER,
      ENEMY,
      OBSTACLE,
      ENEMYBULLET,
      PLAYERBULLET,
      POWERUP,
      NONE
    };

 private:
  std::vector<AComponent*>	_components;
  int				        _id;
  Object::Type		        _type;
  int				        _hp;
  std::pair<int, int>       _movement;
  Object                    *parent;
  char                      _playerID;
  std::vector<Object*>      children;
  double                    _reloadTime;
  double                    _reloading;

 public:
  Object();
  Object(const int id, const Type &type = Type::NONE, const int hp = 1, const int move_x = 0, const int move_y = 0, Object *parent = nullptr, const char playerID = 0);
  ~Object();

  const std::vector<AComponent*>		&getComponents() const;
  int				getId() const;
  Object::Type		getType() const;
  int				getHp() const;
  char              getPlayerID() const;
  const std::pair<int, int> &getMovement() const;
  void              addComponent(AComponent *component);
  void              moveComponents();
  void              moveComponents(const std::pair<int, int> &p);
  void				setComponents(const std::vector<AComponent*> &components);
  void              setType(const Type &type);
  void				setId(const int id);
  void				setHp(const int hp);
  void              setMovement(const int move_x, const int move_y);

  bool              isLoaded() const;
  void              reload();
  void              updateReload(const double &time);

  void              setParent(Object *parent);
  const Object      *getParent() const;
  void              removeChild(Object *child);
  void              addChild(const Object *child);
  const std::vector<Object*>  &getChildren() const;

  friend bool    operator==(const Object &a, const Object &b);
  friend bool    operator<(const Object &a, const Object &b);
};

std::ostream	&operator<<(std::ostream &os, const Object::Type &type);

# include "Hitbox.hh"
# include "Sprite.hh"

std::ostream	&operator<<(std::ostream &os, const Object &obj);

#endif /* !OBJECT_HH_ */
