//
// Sprite.hh for rtype in /home/rochon_k/rendu/rtype/server/include
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:41:04 2016 kevin rochon
// Last update Mon Dec 19 16:57:50 2016 kevin rochon
//

#ifndef SPRITE_HH_
# define SPRITE_HH_

# include <iostream>
# include <string>
# include <utility>
# include "AComponent.hh"

class			Sprite : public AComponent
{
 private:
  std::string		_name;
  std::pair<int, int>	_pos;

 public:
  Sprite(const std::string &name, const int pos_x = 0, const int pos_y = 0);
  ~Sprite();
  const std::pair<int, int>	&getPos() const;
  const std::string		&getName() const;
  void			setPos(const int x, const int y);
  void			setPos(const std::pair<int, int> &pos);
  void			setName(const std::string &name);
};

std::ostream    &operator<<(std::ostream &os, const Sprite &spr);

#endif /* !SPRITE_HH_ */
