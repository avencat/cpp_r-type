//
// Sprite.hh for rtype in /home/rochon_k/rendu/rtype/server/include
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:41:04 2016 kevin rochon
// Last update Mon Dec 19 07:52:08 2016 kevin rochon
//

#ifndef SPRITE_HH_
# define SPRITE_HH_

# include <utility>
# include <string>
# include "AComponent.hpp"

class			Sprite : public AComponent
{
 private:
  std::pair<int, int>	_pos;
  std::string		_name;

 public:
  Sprite(const int id);
  ~Sprite();
  std::pair<int, int>	getPos();
  std::string		getName();
  void			setPos(std::pair<int, int> pos);
  void			setName(std::string name);
};

#endif /* !SPRITE_HH_ */
