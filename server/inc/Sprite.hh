//
// Sprite.hh for rtype in /home/rochon_k/rendu/rtype/server/include
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:41:04 2016 kevin rochon
// Last update Tue Dec 13 19:53:16 2016 kevin rochon
//

#ifndef SPRITE_HH_
# define SPRITE_HH_

# include <utility>
# include <string>

class			Sprite
{
 private:
  std::pair<int, int>	_pos;
  std::string		_name;

 public:
  Sprite();
  ~Sprite();
};

#endif /* !SPRITE_HH_ */
