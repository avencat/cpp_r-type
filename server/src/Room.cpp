//
// Room.cpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/src
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Tue Dec 13 16:44:37 2016 Maxime BOUCHER
// Last update Sat Dec 31 10:53:12 2016 Maxime BOUCHER
//

#include <unistd.h>
#include <chrono>
#include <ctime>
#include "Room.hpp"

Room	*Room::me = NULL;

void	Room::setLevel(const int lvl)
{
  level = lvl;
}

Room::Room()
{
  me = this;
  this->thread.createThread(me);
  end = false;
  active = false;
}
Room::~Room(){}

void	*Room::startThread(void *data)
{
  me = (Room *)data;
  me->loop();
  return NULL;
}

void	Room::loop()
{
  while (end == false)
    queue();
}	

void	Room::queue()
{
  std::list<Client>::iterator	it;
  size_t			count;
  bool				start;
  std::chrono::seconds					sec(10);
  std::chrono::time_point<std::chrono::system_clock>	lap;
  bool							chg;
 
  this->thread = me->thread;
  start = false;
  if (!active)
    me->wait();
  chg = true;
  while (start == false && active == true && end == false)
    {
      if (player.size() == 4)
	state = Full;
      else
	state = Waiting;
      if(player.size() != 0)
	{
	  chg = true;
	  it = player.begin();
	  for (count = 1; count <= player.size(); count++)
	    {
	      if (count == 1)
		start = true;
	      if (it->getIsReady() == false)
		start = false;
	      it++;
	    }
	}
      else
	{
	  if (chg == true)
	    lap = std::chrono::system_clock::now();
	  else if (std::chrono::system_clock::now()-lap > sec)
	    active = false;
	  chg = false;
	}
      if (start == true)
	{
	  play();
	  active = false;
	}
    }
}

void	Room::play()
{
  state = inGame;
  while (state == inGame)
    {
      
    }
}

void	Room::wait()
{
  thread.wait();
}

void	Room::signal()
{
  thread.signal();
}

int	Room::lockMutex()
{
  return (thread.lockMutex());
}

int	Room::unlockMutex()
{
  return (thread.unlockMutex());
}

void	Room::endLoop()
{
  end = true;
}

void	Room::join()
{
  thread.join();
}

void	Room::setActive(const bool state)
{
  active = state;
}

bool	Room::isActive()
{
  return active;
}

size_t	Room::getNbPlayer()
{
  return (player.size());
}

bool	Room::addPlayer(Client &newPlayer)
{
  if (getNbPlayer() >= 4)
    return false;
  player.push_back(newPlayer);
  return true;
}

bool	Room::addViewer(Client &newViewer)
{
  viewer.push_back(newViewer);
  return true;
}

bool	Room::deletePlayer(Client &delPlayer)
{
  std::list<Client>::iterator	it;

  if (getNbPlayer() == 0)
    return false;
  for (it = player.begin(); it != player.end(); it++)
    {
      if (it->getIp() == delPlayer.getIp() && it->getPort() == delPlayer.getPort())
	{
	  player.erase(it);
	  return true;
	}
    }
  return false;
}

bool	Room::deleteViewer(Client &delViewer)
{
  std::list<Client>::iterator	it;

  if (getNbPlayer() == 0)
    return false;
  for (it = player.begin(); it != player.end(); it++)
    {
      if (it->getIp() == delViewer.getIp() && it->getPort() == delViewer.getPort())
	{
	  player.erase(it);
	  return true;
	}
    }
  return false;
}
