//
// ASocket.cpp for Socket in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Thu Dec 15 00:59:07 2016 Jessica VAN-DEN-ZANDE
// Last update Thu Dec 15 01:04:54 2016 Jessica VAN-DEN-ZANDE
//

#include "ASocket.hpp"

ASocket::ASocket()
{
  this->fdClient = 0;
}

ASocket::~ASocket()
{

}

void		ASocket::setUsername(const std::string name)
{
  this->username = name;
}

std::string	ASocket::getUsername(void) const
{
  return this->username;
}

void		ASocket::setFdClient(int fd)
{
  this->fdClient = fd;
}

int		ASocket::getFdClient(void)
{
  return this->fdClient;
}
