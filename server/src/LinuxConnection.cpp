//
// Network.cpp for Network in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Wed Dec 14 15:57:21 2016 Jessica VAN-DEN-ZANDE
// Last update Thu Dec 15 12:47:16 2016 Jessica VAN-DEN-ZANDE
//

#include "LinuxConnection.hpp"

Network::Network() 
{
  this->fdMax = 0;
}

Network::~Network() {}

bool		Network::initServer(int port, int queue)
{
  this->servSocket = socket(AF_INET, SOCK_STREAM, 0);
  bzero((char *) &(this->serv_addr), sizeof(this->serv_addr));
  this->serv_addr.sin_family = AF_INET;
  this->serv_addr.sin_port = htons(port);
  this->serv_addr.sin_addr.s_addr = INADDR_ANY;
  bind(this->servSocket, (struct sockaddr *) &(this->serv_addr), sizeof(this->serv_addr));
  listen(this->servSocket, queue);
  FD_ZERO(&(this->listWriteFd));
  FD_ZERO(&(this->listReadFd));
  this->fdMax = this->servSocket;
  return true;
}

bool		Network::runServer(bool stateServer)
{
  int		rv;

  while (stateServer == true)
    {
      this->timeout.tv_sec = 20;
      this->timeout.tv_usec = 0;
      this->setReadList();
      this->setWriteList();
      rv = select((this->fdMax) + 1, &(this->listReadFd), &(this->listWriteFd), NULL, 
		  &(this->timeout));
      if (rv < 0)
	return false;
      else if (rv == 0)
	std::cout << "Nothing happened." << std::endl;
      else
	checkActivity();
    }
  return (false);
}

void		Network::addSocket()
{
  Socket	newSocket;
  int		socket;
  int		size;

  size = sizeof(this->serv_addr);
  socket = accept(this->servSocket,
		   ((struct sockaddr *)&(this->serv_addr)), (socklen_t *)&size);
  newSocket.setFdClient(socket);
  this->clients.push_back(newSocket);
}

void				Network::deleteSocket(Socket toDelete)
{
  std::list<Socket>::iterator	it;

  for(it = clients.begin(); it != clients.end(); it++)
    {
      if (it->getFdClient() == toDelete.getFdClient())
	{
	  close(it->getFdClient());
	  clients.erase(it);
	  return;
	}
    }
}

void	Network::setReadList(void)
{
  std::list<Socket>::iterator	it;
  int				val;

  FD_ZERO(&(this->listReadFd));
  FD_SET(this->servSocket, &(this->listReadFd));
  if (this->servSocket > this->fdMax)
    this->fdMax = this->servSocket;
  for(it = clients.begin(); it != clients.end(); it++)
    {
      val = it->getFdClient();
      if (val > this->fdMax)
	this->fdMax = val;
      FD_SET(val, &(this->listReadFd));
    }
}

void	Network::setWriteList(void)
{
  std::list<Socket>::iterator	it;
  int				val;

  FD_ZERO(&(this->listWriteFd));
  FD_SET(this->servSocket, &(this->listWriteFd));
  if (this->servSocket > this->fdMax)
    this->fdMax = this->servSocket;
  for(it = clients.begin(); it != clients.end(); it++)
    {
      val = it->getFdClient();
      if (val > this->fdMax)
	this->fdMax = val;
      FD_SET(val, &(this->listWriteFd));
    }
}

void	Network::checkActivity(void)
{
  std::list<Socket>::iterator	it;
  int				val;

  if (FD_ISSET(this->servSocket, &(this->listReadFd)))
    {
      std::cout << "New client." << std::endl;
      this->addSocket();
    }
  else
    {
      for(it = this->clients.begin(); it != this->clients.end(); it++)
    	{
    	  val = it->getFdClient();
	  if (FD_ISSET(val, &(this->listReadFd)))
	    {
	      std::cout << "Client is talking to us." << std::endl;
	    }
    	}
    }
}
