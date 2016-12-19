//
// Hitbox.hh for rtype in /home/rochon_k/rendu/rtype/server/include
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:42:23 2016 kevin rochon
// Last update Mon Dec 19 17:11:32 2016 kevin rochon
//

#ifndef HITBOX_HH_
# define HITBOX_HH_

# include <utility>
# include "AComponent.hh"

class			Hitbox : public AComponent
{
 private:
  std::pair<int, int>	_pos;
  int			_size;

 public:
  Hitbox(const int id, const int size);
  ~Hitbox();
  std::pair<int, int>	getPos() const;
  int			getSize() const;
  void			setPos(int x, int y);
  void			setSize(int _size);
};

#endif /* !HITBOX_HH_ */
