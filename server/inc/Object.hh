//
// Object.hh for rtype in /home/rochon_k/rendu/rtype/server/include
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:41:55 2016 kevin rochon
// Last update Tue Dec 13 19:59:22 2016 kevin rochon
//

#ifndef OBJECT_HH_
# define OBJECT_HH_

# include <list>

class				Object
{
 public:
  enum				Type
    {
      PLAYER,
      ENEMIE,
      OBSTACLE,
      ENEMIEBULLET,
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
}

#endif /* !OBJECT_HH_ */
