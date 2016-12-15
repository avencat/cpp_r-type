//
// Room.cpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/src
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Tue Dec 13 16:44:37 2016 Maxime BOUCHER
// Last update Thu Dec 15 15:52:19 2016 Maxime BOUCHER
//

#include <unistd.h>
#include "../inc/Room.hpp"

Room	*Room::me = NULL;

void	Room::setLevel(const int lvl)
{
  level = lvl;
}

Room::Room()
{
  me = this;
  this->thread.createThread(me);
}
Room::~Room(){}

void	*Room::startThread(void *data)
{
  me->loop();
  return NULL;
}

int	Room::loop()
{
  this->thread = me->thread;
  thread.trylockLoop();
  while (thread.trylockLoop() != 0)
}
int	Room::lockLock()
{
  return (thread.lockLock());
}

int	Room::unlockLock()
{
  return (thread.unlockLock());
}

int	Room::endLoop()
{
  std::cout << "endloop" << std::endl;
  return (thread.endLoop());
}

void	Room::join()
{
  thread.join();
}
