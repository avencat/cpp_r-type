//
// Client.cpp for Player in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Thu Dec 15 01:05:16 2016 Jessica VAN-DEN-ZANDE
// Last update Sat Dec 31 10:27:57 2016 Jessica VAN-DEN-ZANDE
//

#include "Client.hpp"

Client::Client() 
{
  this->isReady = false;
  this->score = 0;
  this->lives = 3;
  this->powerup = 0;
  this->syn = 0;
  this->ack = 0;
  this->synState = false;
  this->ackState = false;
}

Client::~Client() {}

void			Client::setIsReady(bool state)
{
  this->isReady = state;
}
bool			Client::getIsReady(void)
{
  return this->isReady;
}
void			Client::setScore(int nb)
{
  this->score = nb;
}
int			Client::getScore(void)
{
  return this->score;
}
void			Client::setLives(int nb)
{
  this->lives = nb;
}
int			Client::getLives(void)
{
  return this->lives;
}
void			Client::setPowerup(int nb)
{
  this->powerup = nb;
}
int			Client::getPowerup(void)
{
  return this->powerup;
}

void			Client::setUsername(const std::string name)
{
  this->username = name;
}

std::string		Client::getUsername(void) const
{
  return this->username;
}

void			Client::setIp(std::string ip)
{
  this->ip = ip;
}

std::string		Client::getIp(void) const
{
  return this->ip;
}

void			Client::setPort(const int port)
{
  this->port = port;
}

int			Client::getPort(void) const
{
  return this->port;
}

void			Client::setSyn(int syn)
{
  this->syn = syn;
}

int			Client::getSyn(void) const
{
  return syn;
}

void			Client::setAck(int ack)
{
  this->ack = ack;
}

int			Client::getAck(void) const
{
  return ack;
}

void			Client::setSynState(bool state)
{
  this->synState = state;
}

bool			Client::getSynState(void) const
{
  return synState;
}

void			Client::setAckState(bool state)
{
  this->ackState = state;
}

bool			Client::getAckState(void) const
{
  return ackState;
}

// void			Client::setclientAddr(struct sockaddr_in clientAddr)
// {
//   this->clientAddr = clientAddr;
// }

// struct sockaddr_in	Client::getclientAddr(void)
// {
//   return this->clientAddr;
// }

bool			Client::operator==(const Client &client)
{
  return this->ip == client.getIp() && this->port == client.getPort();
}

bool			Client::operator==(const std::string &str)
{
  return this->ip == str;
}
