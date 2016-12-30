//
// Room.cpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/src
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Tue Dec 13 16:44:37 2016 Maxime BOUCHER
// Last update Fri Dec 30 14:51:25 2016 Maxime BOUCHER
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
  std::cout << "thread fini" << std::endl;
  return NULL;
}

void	Room::loop()
{
  while (end == false)
    queue();
}	

void	Room::queue()
{
  std::list<Socket>::iterator	it;
  size_t			count;
  bool				start;
  std::chrono::seconds					sec(10);
  std::chrono::time_point<std::chrono::system_clock>	lap;
  bool							chg;
 
  this->thread = me->thread;
  start = false;
  sleep(1);
  me->wait();
  chg = false;
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
	play();
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

bool	Room::addPlayer(Socket &newPlayer)
{
  if (getNbPlayer() >= 4)
    return false;
  player.push_back(newPlayer);
  return true;
}

bool	Room::addViewer(Socket &newViewer)
{
  viewer.push_back(newViewer);
  return true;
}

bool	Room::deletePlayer(Socket &delPlayer)
{
  std::list<Socket>::iterator	it;

  if (getNbPlayer() == 0)
    return false;
  for (it = player.begin(); it != player.end(); it++)
    {
      if (it->getFdClient() == delPlayer.getFdClient())
	{
	  player.erase(it);
	  return true;
	}
    }
  return false;
}

bool	Room::deleteViewer(Socket &delViewer)
{
  std::list<Socket>::iterator	it;

  if (getNbPlayer() == 0)
    return false;
  for (it = player.begin(); it != player.end(); it++)
    {
      if (it->getFdClient() == delViewer.getFdClient())
	{
	  player.erase(it);
	  return true;
	}
    }
  return false;
}
