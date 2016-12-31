//
// AClient.cpp for Client in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Thu Dec 15 00:59:07 2016 Jessica VAN-DEN-ZANDE
// Last update Sat Dec 31 10:27:39 2016 Jessica VAN-DEN-ZANDE
//

#include "AClient.hpp"

AClient::AClient() {}

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

// void			AClient::setclientAddr(struct sockaddr_in &clientAddr)
// {
//   this->clientAddr = clientAddr;
// }

// struct sockaddr_in    AClient::getclientAddr(void)
// {
//   return this->clientAddr;
// }

bool		AClient::operator==(const AClient &client)
{
  return this->ip == client.getIp() && this->port == client.getPort();
}

bool		AClient::operator==(const std::string &str)
{
  return this->ip == str;
}
