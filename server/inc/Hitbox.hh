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

# include <iostream>
# include <string>
# include <utility>
# include "AComponent.hh"

class			Hitbox : public AComponent
{
 private:
  std::pair<int, int>	_pos;
  std::pair<int, int>	_size;

 public:
  Hitbox(const int pos_x = 0, const int pos_y = 0, const int size_x = 1, const int size_y = 1);
  ~Hitbox();
  const std::pair<int, int>	&getPos() const;
  const std::pair<int, int>	&getSize() const;
  void			    setPos(const int x, const int y);
  void			    setPos(const std::pair<int, int> &pos);
  void			    setSize(const int x, const int y);
  void			    setSize(const std::pair<int, int> &size);

  bool              doesCollide(const Hitbox &hb) const;
};

std::ostream    &operator<<(std::ostream &os, const Hitbox &hbx);

#endif /* !HITBOX_HH_ */
