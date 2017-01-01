//
// ThreadLinux.hpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/inc
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Wed Dec 14 16:26:49 2016 Maxime BOUCHER
// Last update Sun Jan  1 16:01:54 2017 Maxime BOUCHER
//

#ifndef THREADLINUX_HPP_
# define THREADLINUX_HPP_

#include <iostream>
#include <pthread.h>
#include "AThread.hpp"

class		Room;

class		Thread:public AThread
{
private:
  pthread_t		thread;
  pthread_mutex_t	lock;
  pthread_mutex_t	player;
  pthread_cond_t	waiting;

public:
  Thread();
  ~Thread();
  virtual void		createThread(Room *);
  virtual void		deleteThread();
  int			unlockMutex();
  int			lockMutex();
  int			unlockPlayer();
  int			lockPlayer();
  void			wait();
  void			signal();
  void			join();
};

#endif /* !THREADLINUX_HPP_ */
