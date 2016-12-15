//
// AThread.hpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/inc
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Tue Dec 13 16:45:02 2016 Maxime BOUCHER
// Last update Thu Dec 15 14:57:08 2016 Maxime BOUCHER
//

#ifndef ATHREAD_HPP_
# define ATHREAD_HPP_

#include <iostream>
#include <pthread.h>

class		Room;

class		AThread
{
public:
  AThread();
  virtual ~AThread();
  virtual void	createThread(Room *) = 0;
  virtual void	deleteThread() = 0;
};

#endif /* !ATHREAD_HPP_ */
