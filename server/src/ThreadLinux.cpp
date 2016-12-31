//
// ThreadLinux.cpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/src
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Wed Dec 14 17:01:58 2016 Maxime BOUCHER
// Last update Fri Dec 30 16:56:48 2016 Maxime BOUCHER
//

#include "ThreadLinux.hpp"
#include "Room.hpp"

Thread::Thread()
{
  lock = PTHREAD_MUTEX_INITIALIZER;
  waiting = PTHREAD_COND_INITIALIZER;
}
Thread::~Thread(){}

void	Thread::createThread(Room *me)
{
  pthread_create(&thread, NULL, &Room::startThread, me);
}

void	Thread::deleteThread(){}

int	Thread::lockMutex()
{
  pthread_mutex_lock(&lock);
  return (0);
}

void	Thread::wait()
{
  pthread_mutex_lock(&lock);
  pthread_cond_wait(&waiting, &lock);
  pthread_mutex_unlock(&lock);
}

void	Thread::signal()
{
  pthread_cond_broadcast(&waiting);
}

int	Thread::unlockMutex()
{
  return (pthread_mutex_unlock(&lock));
}

void	Thread::join()
{
  pthread_join(thread, NULL);
}
