//
// Room.cpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/src
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Tue Dec 13 16:44:37 2016 Maxime BOUCHER
// Last update Sun Jan  1 14:29:48 2017 Maxime BOUCHER
//

#include <unistd.h>
#include <chrono>
#include "Room.hpp"

void	Room::setLevel(const int lvl)
{
  level = lvl;
}

std::vector<std::string>	Room::getPlayers()
{
  std::vector<std::string>	vec;

  for (std::list<Player*>::iterator it = player.begin(); it != player.end(); it++)
    {
      vec.push_back((*it)->getUsername());
    }
  return vec;
}

Room::Room(short tic, int i)
{
  ticrate = tic;
  id = i;
  end = false;
  active = false;
  this->thread.createThread(this);
}
Room::~Room(){}

void	*Room::startThread(void *data)
{
  Room	*me;

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
  std::list<Player*>::iterator				it;
  size_t						count;
  bool							start;
  std::chrono::seconds					sec(10);
  std::chrono::time_point<std::chrono::system_clock>	lap;
  bool							chg;

  start = false;
  if (!active)
    wait();
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
	  for (count = 1; count <= player.size(); count++, it++)
	    {
	      if (count == 1)
		start = true;
	      if ((*it)->getIsReady() == false)
		start = false;
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
  while (end == false)
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

Thread	&Room::getThread()
{
  return (thread);
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

eState	Room::getState()
{
  return state;
}

int	Room::getId()
{
  return (id);
}

std::vector<std::string>	Room::addPlayer(Player *newPlayer)
{
  std::vector<std::string>	vec;

  if (getNbPlayer() >= 4)
    return vec;
  player.push_back(newPlayer);
  return getPlayers();
}

bool	Room::addViewer(Player *newViewer)
{
  viewer.push_back(newViewer);
  return true;
}

bool	Room::deletePlayer(Player *delPlayer)
{
  std::list<Player*>::iterator	it;

  if (getNbPlayer() == 0)
    return false;
  for (it = player.begin(); it != player.end(); it++)
    {
      if ((*it)->getIp() == delPlayer->getIp() && (*it)->getPort() == delPlayer->getPort())
	{
	  player.erase(it);
	  return true;
	}
    }
  return false;
}

bool	Room::deleteViewer(Player *delViewer)
{
  std::list<Player*>::iterator	it;

  if (getNbPlayer() == 0)
    return false;
  for (it = player.begin(); it != player.end(); it++)
    {
      if ((*it)->getIp() == delViewer->getIp() && (*it)->getPort() == delViewer->getPort())
	{
	  player.erase(it);
	  return true;
	}
    }
  return false;
}

bool	Room::findPlayer(const AClient &playerToFind)
{
  std::list<Player*>::iterator	it;

  for (it = player.begin(); it != player.end(); it++)
    {
      if (playerToFind.getIp() == (*it)->getIp())
	return true;
    }
  return false;
}
