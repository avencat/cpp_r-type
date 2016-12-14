//
// Room.cpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/src
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Tue Dec 13 16:44:37 2016 Maxime BOUCHER
// Last update Wed Dec 14 22:30:29 2016 Maxime BOUCHER
//

#include "../inc/Room.hpp"

Room::Room()
{
  Thread	thread;
  me = this;
  thread.createThread(me);
}
Room::~Room(){}

void	*Room::startThread(void *data)
{
  std::cout << "thread started" << std::endl;
  return NULL;
}
