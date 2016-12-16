//
// Client.cpp for Player in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Thu Dec 15 01:05:16 2016 Jessica VAN-DEN-ZANDE
// Last update Thu Dec 15 11:42:25 2016 Jessica VAN-DEN-ZANDE
//

#include "Socket.hpp"

Socket::Socket() 
{
  this->isReady = false;
  this->score = 0;
  this->lives = 3;
  this->powerup = 0;
}

Socket::~Socket() {}

void	Socket::setIsReady(bool state)
{
  this->isReady = state;
}
bool	Socket::getIsReady(void)
{
  return this->isReady;
}
void	Socket::setScore(int nb)
{
  this->score = nb;
}
int	Socket::getScore(void)
{
  return this->score;
}
void	Socket::setLives(int nb)
{
  this->lives = nb;
}
int	Socket::getLives(void)
{
  return this->lives;
}
void	Socket::setPowerup(int nb)
{
  this->powerup = nb;
}
int	Socket::getPowerup(void)
{
  return this->powerup;
}

void		Socket::setUsername(const std::string name)
{
  this->username = name;
}

std::string	Socket::getUsername(void) const
{
  return this->username;
}

void		Socket::setFdClient(int fd)
{
  this->fdClient = fd;
}

int		Socket::getFdClient(void)
{
  return this->fdClient;
}
