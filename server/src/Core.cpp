//
// Core.cpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/src
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Thu Dec 29 13:55:14 2016 Maxime BOUCHER
// Last update Fri Dec 30 16:05:31 2016 Maxime BOUCHER
//

#include "Core.hpp"

Core::Core(){}
Core::~Core(){}

void		Core::initRooms()
{
  for (int i = 0; i < 1; ++i)
    waiting_rooms.push_back(new Room);
}

void		Core::checkRooms()
{
  std::list<Room*>::iterator	it;

  for (it = active_rooms.begin(); it != active_rooms.end(); it++)
    {
      if ((*it)->isActive() == false)
	{
	  waiting_rooms.push_back(*it);
	  active_rooms.erase(it);
	}
    }
}

bool		Core::activateRoom()
{
  if (waiting_rooms.empty())
    return false;
  waiting_rooms.front()->signal();
  waiting_rooms.front()->setActive(true);
  active_rooms.splice(active_rooms.end(),waiting_rooms, waiting_rooms.begin());
  return true;
}

size_t		Core::sizeActivate()
{
  return active_rooms.size();
}

void		Core::endAll()
{
  std::list<Room*>::iterator	it;

  while (!waiting_rooms.empty())
    activateRoom();
  for (it = active_rooms.begin(); it != active_rooms.end(); it++)
    {
      (*it)->endLoop();
      (*it)->join();
    }
}
