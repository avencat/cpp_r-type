//
// ThreadLinux.cpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/src
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Wed Dec 14 17:01:58 2016 Maxime BOUCHER
// Last update Thu Dec 15 15:35:40 2016 Maxime BOUCHER
//

#include <pthread.h>
#include "../inc/ThreadLinux.hpp"
#include "../inc/Room.hpp"

Thread::Thread()
{
  loop = PTHREAD_MUTEX_INITIALIZER;
  lock = PTHREAD_MUTEX_INITIALIZER;
}
Thread::~Thread(){}

void	Thread::createThread(Room *me)
{
  pthread_create(&thread, NULL, &Room::startThread, me);
}

void	Thread::deleteThread(){}

int	Thread::trylockLoop()
{
  std::cout << "trylock" << std::endl;
  return (pthread_mutex_trylock(&loop));
}

int	Thread::lockLock()
{
  pthread_mutex_lock(&lock);
  return (0);
}

int	Thread::unlockLock()
{
  return (pthread_mutex_unlock(&lock));
}

int	Thread::endLoop()
{
  std::cout << "mutex end loop" << std::endl;
  return (pthread_mutex_unlock(&loop));
}

void	Thread::join()
{
  pthread_join(thread, NULL);
}
