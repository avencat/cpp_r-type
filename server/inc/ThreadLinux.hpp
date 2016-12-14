//
// ThreadLinux.hpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/inc
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Wed Dec 14 16:26:49 2016 Maxime BOUCHER
// Last update Wed Dec 14 22:08:06 2016 Maxime BOUCHER
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
  pthread_t	thread;

public:
  Thread();
  ~Thread();
  virtual void		createThread(Room *);
  virtual void		deleteThread();
};

#endif /* !THREADLINUX_HPP_ */
