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

# include <utility>
# include <string>
# include "AComponent.hh"

class			Sprite : public AComponent
{
 private:
  std::pair<int, int>	_pos;
  std::string		_name;

 public:
  Sprite(const int id, const std::string name);
  ~Sprite();
  std::pair<int, int>	getPos() const;
  std::string		getName() const;
  void			setPos(int x, int y);
  void			setName(std::string name);
};

#endif /* !SPRITE_HH_ */
