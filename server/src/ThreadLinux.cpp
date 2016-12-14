//
// ThreadLinux.cpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/src
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Wed Dec 14 17:01:58 2016 Maxime BOUCHER
// Last update Wed Dec 14 22:33:00 2016 Maxime BOUCHER
//

#include "../inc/ThreadLinux.hpp"
#include "../inc/Room.hpp"

Thread::Thread(){}
Thread::~Thread(){}

void	Thread::createThread(Room *me)
{
  pthread_create(&thread, NULL, &Room::startThread, me);
}

void	Thread::deleteThread(){}
