//
// Room.cpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/src
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Tue Dec 13 16:44:37 2016 Maxime BOUCHER
// Last update Sun Jan  1 16:29:56 2017 Maxime BOUCHER
//

#include <unistd.h>
#include <chrono>
#include "Room.hpp"

void	Room::setLevel(const int lvl)
{
  lockMutex();
  level = lvl;
  unlockMutex();
}

std::vector<std::string>	Room::getPlayers()
{
  std::vector<std::string>	vec;

  lockMutex();
  for (std::list<Player*>::iterator it = player.begin(); it != player.end(); it++)
    {
      vec.push_back((*it)->getUsername());
    }
  unlockMutex();
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
  lockMutex();
  while (start == false && active == true && end == false)
    {
      unlockMutex();
      lockPlayer();
      lockMutex();
      if (player.size() == 4)
	state = Full;
      else
	state = Waiting;
      unlockMutex();
      if(player.size() != 0)
	{
	  unlockPlayer();
	  chg = true;
	  lockPlayer();
	  it = player.begin();
	  for (count = 1; count <= player.size(); count++, it++)
	    {
	      if (count == 1)
		start = true;
	      if ((*it)->getIsReady() == false)
		start = false;
	    }
	  unlockPlayer();
	}
      else
	{
	  unlockPlayer();
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
      lockMutex();
    }
  unlockMutex();
}

void	Room::play()
{
  lockMutex();
  state = inGame;
  unlockMutex();
  while (end == false)
    {
      
    }
}

void	Room::setId(const int newid)
{
  lockMutex();
  id = newid;
  unlockMutex();
}

void	Room::wait()
{
  thread.wait();
}

void	Room::signal()
{
  thread.signal();
}

int	Room::lockPlayer()
{
  return (thread.lockPlayer());
}

int	Room::unlockPlayer()
{
  return (thread.unlockPlayer());
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
  lockMutex();
  end = true;
  unlockMutex();
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
  lockMutex();
  active = state;
  unlockMutex();
}

bool	Room::isActive()
{
  bool	tmp;

  lockMutex();
  tmp = active;
  unlockMutex();
  return tmp;
}

size_t	Room::getNbPlayer()
{  
  size_t	tmp;

  lockMutex();
  tmp = player.size();
  unlockMutex();
  return tmp;
}

size_t	Room::getNbViewer()
{
  size_t	tmp;

  lockMutex();
  tmp = viewer.size();
  unlockMutex();
  return tmp;
}

eState	Room::getState()
{
  eState	tmp;
  lockMutex();
  tmp = state;
  unlockMutex();
  return tmp;
}

int	Room::getId()
{
  int	tmp;

  lockMutex();
  tmp = id;
  unlockMutex();
  return (tmp);
}

std::vector<std::string>	Room::addPlayer(Player *newPlayer)
{
  std::vector<std::string>	vec;

  lockPlayer();
  if (getNbPlayer() >= 4)
    {
      unlockPlayer();
      return vec;
    }
  player.push_back(newPlayer);
  unlockPlayer();
  return getPlayers();
}

bool	Room::addViewer(Player *newViewer)
{
  lockMutex();
  viewer.push_back(newViewer);
  unlockMutex();
  return true;
}

bool	Room::deletePlayer(Player *delPlayer)
{
  std::list<Player*>::iterator	it;

  lockPlayer();
  if (getNbPlayer() == 0)
    {
      unlockPlayer();
      return false;
    }
  for (it = player.begin(); it != player.end(); it++)
    {
      if ((*it)->getIp() == delPlayer->getIp() && (*it)->getPort() == delPlayer->getPort())
	{
	  player.erase(it);
	  unlockPlayer();
	  return true;
	}
    }
  unlockPlayer();
  return false;
}

bool	Room::deleteViewer(Player *delViewer)
{
  std::list<Player*>::iterator	it;

  lockMutex();
  if (getNbViewer() == 0)
    {
      unlockMutex();
      return false;
    }
  for (it = viewer.begin(); it != viewer.end(); it++)
    {
      if ((*it)->getIp() == delViewer->getIp() && (*it)->getPort() == delViewer->getPort())
	{
	  viewer.erase(it);
	  unlockMutex();
	  return true;
	}
    }
  unlockMutex();
  return false;
}

bool	Room::findPlayer(const AClient &playerToFind)
{
  std::list<Player*>::iterator	it;

  lockPlayer();
  for (it = player.begin(); it != player.end(); it++)
    {
      if (playerToFind.getIp() == (*it)->getIp())
	{
	  unlockPlayer();
	  return true;
	}
    }
  unlockPlayer();
  return false;
}
