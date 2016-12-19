//
// Object.hh for rtype in /home/rochon_k/rendu/rtype/server/include
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:41:55 2016 kevin rochon
// Last update Mon Dec 19 17:06:41 2016 kevin rochon
//

#ifndef OBJECT_HH_
# define OBJECT_HH_

# include <list>
# include <string>
# include "AComponent.hh"
# include "Sprite.hh"
# include "Hitbox.hh"

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
  std::list<AComponent*>	getComponents() const;
  int				getId() const;
  Object::Type			getType() const;
  int				getHp() const;
  void				setComponents(std::list<AComponent*> components);
  void				setId(int id);
  void				setType(Object::Type type);
  void				setHp(int hp);
};

#endif /* !OBJECT_HH_ */
