//
// Room.hpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/inc
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Tue Dec 13 16:45:23 2016 Maxime BOUCHER
// Last update Sun Jan  1 15:32:05 2017 Maxime BOUCHER
//

#ifndef ROOM_HPP_
# define ROOM_HPP_

# include <list>
# include <iostream>
# include "AClient.hpp"
# include "Player.hpp"
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
  std::list<Player*>	player;
  std::list<Player*>	viewer;
  short			ticrate;
  int			id;
  eState		state;
  int			level;
  std::string		nameBestScore;
  int			highScore;
  bool			active;
  Thread		thread;
  bool			end;

public:
  Room(short, int);
  ~Room();

  std::vector<std::string>	getPlayers();
  size_t			getNbPlayer();
  eState			getState();
  static void			*startThread(void *data);
  int				unlockMutex();
  int				lockMutex();
  void				endLoop();
  void				join();
  void				loop();
  void				queue();
  void				setLevel(const int);
  size_t			getNbViewer();
  int				getId();
  bool				findPlayer(const AClient &);
  std::vector<std::string>	addPlayer(Player *);
  bool				addViewer(Player *);
  bool				deletePlayer(Player *);
  bool				deleteViewer(Player *);
  bool				isActive();
  void				setId(const int);
  void				setActive(const bool);
  void				play();
  void				wait();
  void				signal();
  Thread			&getThread();
};

#endif /* !ROOM_HPP_ */
