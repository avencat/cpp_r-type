//
// Room.hpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/inc
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Tue Dec 13 16:45:23 2016 Maxime BOUCHER
// Last update Thu Dec 15 15:44:08 2016 Maxime BOUCHER
//

#ifndef ROOM_HPP_
# define ROOM_HPP_

# include <list>
# include <iostream>
# include "ThreadLinux.hpp"

class		Room
{
private:
  //std::list <Socket>	player;
  //std::list <Socket>	viewer;
  static Room			*me;
  int			id;
  int			state;
  int			level;
  std::string		nameBestScore;
  int			highScore;
  Thread		thread;

public:
  Room();
  ~Room();
  int			getNbPlayer();
  static void		*startThread(void *data);
  int			unlockLock();
  int			lockLock();
  int			endLoop();
  void			join();
  int			loop();
  void			setLevel(const int);
};

#endif /* !ROOM_HPP_ */
