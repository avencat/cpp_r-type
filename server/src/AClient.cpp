//
// AClient.cpp for Client in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Thu Dec 15 00:59:07 2016 Jessica VAN-DEN-ZANDE
// Last update Sun Jan  1 16:55:53 2017 Jessica VAN-DEN-ZANDE
//

#include "AClient.hpp"

AClient::AClient() {}

AClient::AClient(const AClient &client)
{
  this->ip = client.ip;
  this->port = client.port;
  this->username = client.username;
  this->clientAddr = client.clientAddr;
  this->state = NEW;
  this->isInRoom = false;
  this->ack = 0;
  this->syn = 0;
}

AClient::~AClient() {}

void			AClient::setIp(const std::string ip)
{
  this->ip = ip;
}

std::string		AClient::getIp(void) const
{
  return this->ip;
}

void			AClient::setPort(const int port)
{
  this->port = port;
}

int			AClient::getPort(void) const
{
  return this->port;
}

void			AClient::setUsername(const std::string name)
{
  this->username = name;
}

std::string		AClient::getUsername(void) const
{
  return this->username;
}

void			AClient::setSyn(int syn)
{
  this->syn = syn;
}

int			AClient::getSyn(void) const
{
  return syn;
}

void			AClient::setAck(int ack)
{
  this->ack = ack;
}

int			AClient::getAck(void) const
{
  return ack;
}

void			AClient::setState(const AClient::State &state)
{
  this->state = state;
}
const AClient::State  	&AClient::getState() const
{
  return this->state;
}

std::vector<std::string>	&AClient::getMsgQueue()
{
  return this->msgQueue;
}

void			AClient::setclientAddr(struct sockaddr_in &clientAddr)
{
  this->clientAddr = clientAddr;
}

struct sockaddr_in    &AClient::getclientAddr(void)
{
  return this->clientAddr;
}

void			AClient::setIsInRoom(bool state)
{
  this->isInRoom = state;
}

bool			AClient::getIsInRoom()
{
  return this->isInRoom;
}

void			AClient::addMsgInQueue(const std::string &msg)
{
  msgQueue.push_back(msg);
}

bool			AClient::operator==(const AClient &client)
{
  return this->ip == client.getIp() && this->port == client.getPort();
}

bool			AClient::operator==(const std::string &str)
{
  return this->ip == str;
}

bool			AClient::operator==(const struct sockaddr_in &client)
{
  return this->ip == inet_ntoa(client.sin_addr) && this->port == ntohs(client.sin_port);
}
