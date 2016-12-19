//
// Object.hh for rtype in /home/rochon_k/rendu/rtype/server/include
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:41:55 2016 kevin rochon
// Last update Mon Dec 19 08:05:58 2016 kevin rochon
//

#ifndef OBJECT_HH_
# define OBJECT_HH_

# include <list>
# include "AComponent.hpp"

class		Object
{
 public:
  enum		Type
    {
      PLAYER,
      ENEMY,
      OBSTACLE,
      ENEMYBULLET,
      PLAYERBULLET,
      POWERUP
    };

 private:
  std::list<AComponent*>	_components;
  int				_id;
  Object::Type			_type;
  int				_hp;

 public:
  Object();
  ~Object();
  std::list<AComponent*>	getComponents();
  int				getId();
  Object::Type			getType();
  int				getHp();
  void				setComponents(std::list<AComponent*> components);
  void				setId(int id);
  void				setType(Object::Type type);
  void				setHp(int hp);
};

#endif /* !OBJECT_HH_ */
