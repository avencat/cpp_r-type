//
// ThreadLinux.hpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/inc
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Wed Dec 14 16:26:49 2016 Maxime BOUCHER
// Last update Thu Dec 15 15:33:56 2016 Maxime BOUCHER
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
  pthread_mutex_t	loop;
  pthread_mutex_t	lock;

public:
  Thread();
  ~Thread();
  virtual void		createThread(Room *);
  virtual void		deleteThread();
  int			trylockLoop();
  int			unlockLock();
  int			lockLock();
  int			endLoop();
  void			join();
};

#endif /* !THREADLINUX_HPP_ */
