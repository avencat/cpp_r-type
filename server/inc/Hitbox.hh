//
// Hitbox.hh for rtype in /home/rochon_k/rendu/rtype/server/include
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:42:23 2016 kevin rochon
// Last update Mon Dec 19 08:12:03 2016 kevin rochon
//

#ifndef HITBOX_HH_
# define HITBOX_HH_

# include <utility>
# include "AComponent.hpp"

class			Hitbox : public AComponent
{
 private:
  std::pair<int, int>	_pos;
  int			_size;

 public:
  Hitbox(const int id);
  ~Hitbox();
  std::pair<int, int>	getPos();
  int			getSize();
  void			setPos(std::pair<int, int> _pos);
  void			setSize(int _size);
};

#endif /* !HITBOX_HH_ */
