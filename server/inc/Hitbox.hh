//
// Hitbox.hh for rtype in /home/rochon_k/rendu/rtype/server/include
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:42:23 2016 kevin rochon
// Last update Tue Dec 13 19:58:42 2016 kevin rochon
//

#ifndef HITBOX_HH_
# define HITBOX_HH_

# include <utility>

class			Hitbox
{
 private:
  std::pair<int, int>	_pos;
  int			_size;

 public:
  Hitbox();
  ~Hitbox();
};

#endif /* !HITBOX_HH_ */
