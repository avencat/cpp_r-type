//
// Room.hpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/inc
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Tue Dec 13 16:45:23 2016 Maxime BOUCHER
// Last update Wed Dec 14 22:31:34 2016 Maxime BOUCHER
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
  Room			*me;
  int			id;
  int			state;
  int			level;
  std::string		nameBestScore;
  int			highScore;
  pthread_t		thread;

public:
  Room();
  ~Room();
  int			getNbPlayer();
  static void			*startThread(void *data);
};

#endif /* !ROOM_HPP_ */
