//
// Core.cpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/src
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Thu Dec 29 13:55:14 2016 Maxime BOUCHER
// Last update Sun Jan  1 12:06:30 2017 Maxime BOUCHER
//

#include "Core.hpp"

Core::Core(){}
Core::~Core(){}

void		Core::initRooms(int tic)
{
  for (int i = 0; i < 8; ++i)
    waiting_rooms.push_back(new Room(tic, i));
}

bool		Core::lockPlayerRoom(const AClient player, const bool lock)
{
  std::list<Room*>::iterator	it;

  for (it = waiting_rooms.begin(); it != waiting_rooms.end(); it++)
    {
      if ((*it)->findPlayer(player) == true)
	{
	  if (lock == true)
	    (*it)->lockMutex();
	  else
	    (*it)->unlockMutex();
	  return true;
	}
    }
  return false;
}

void		Core::checkRooms()
{
  std::list<Room*>::iterator	it;
  std::list<Room*>::iterator	tmp;

  it = active_rooms.begin();
  while (it != active_rooms.end())
    {
      if ((*it)->isActive() == false)
	{
	  waiting_rooms.push_back(*it);
	  tmp = it;
	  it++;
	  active_rooms.erase(tmp);
	}
      else
	it++;
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

std::list<Room*>	Core::getListRoom()
{
  return active_rooms;
}

size_t		Core::sizeActivate()
{
  return active_rooms.size();
}

void		Core::endAll()
{
  std::list<Room*>::iterator	it;

  while (!waiting_rooms.empty())
    {
      activateRoom();
      it = active_rooms.begin();
      (*it)->endLoop();
      (*it)->join();      
    }
}
