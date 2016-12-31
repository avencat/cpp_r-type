//
// Room.hpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/inc
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Tue Dec 13 16:45:23 2016 Maxime BOUCHER
// Last update Sat Dec 31 10:51:28 2016 Maxime BOUCHER
//

#ifndef ROOM_HPP_
# define ROOM_HPP_

# include <list>
# include <iostream>
# include "Socket.hpp"
# include "Client.hpp"
# include "ThreadLinux.hpp"

enum		eState
  {
    Waiting,
    Full,
    inGame
  };

class		Room
{
private:
  std::list<Client>	player;
  std::list<Client>	viewer;
  int			id;
  eState		state;
  int			level;
  std::string		nameBestScore;
  int			highScore;
  bool			active;
  static Room		*me;
  Thread		thread;
  bool			end;

public:
  Room();
  ~Room();

  size_t		getNbPlayer();
  static void		*startThread(void *data);
  int			unlockMutex();
  int			lockMutex();
  void			endLoop();
  void			join();
  void			loop();
  void			queue();
  void			setLevel(const int);
  size_t		getNbViewer();
  bool			addPlayer(Client &);
  bool			addViewer(Client &);
  bool			deletePlayer(Client &);
  bool			deleteViewer(Client &);
  bool			isActive();
  void			setActive(const bool);
  void			play();
  void			wait();
  void			signal();
};

#endif /* !ROOM_HPP_ */
