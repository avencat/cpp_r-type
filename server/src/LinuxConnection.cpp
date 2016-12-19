//
// Network.cpp for Network in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Wed Dec 14 15:57:21 2016 Jessica VAN-DEN-ZANDE
// Last update Mon Dec 19 23:50:15 2016 Jessica VAN-DEN-ZANDE
//

#include "../inc/LinuxConnection.hpp"
#include "../../common/inc/RtypeProtocol.hh"

Network::Network() 
{
  this->fdMax = 0;
  this->msgReceived = NULL;
}

Network::~Network() {}

bool		Network::sendMsg(int fdSocket, void *msgToSend, const size_t &dataSize)
{
  if (send(fdSocket, msgToSend, dataSize, 0) == false)
    {
      std::cerr << "Send message failed." << std::endl;
      return false;
    }
  return true;
}

bool		Network::receiveMsg(int fdSocket, const size_t &dataSize)
{
  int		rv;

  //memset(this->msgReceived, 0, 1000);
  rv = recv(fdSocket, this->msgReceived, dataSize, 0);
  if (rv == -1)
    {
      std::cerr << "Received message failed." << std::endl;
      return false;
    }
  return true;
}

bool		Network::initServer(int port, int queue)
{
  this->servSocket = socket(AF_INET, SOCK_STREAM, 0);
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

void				Network::setReadList(void)
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

void				Network::setWriteList(void)
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

void				Network::checkActivity(void)
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
	      if (securiseConnection(*it) == false)
		{
		  std::cerr << "Connection not secure, closing socket..." << std::endl;
		}
	    }
    	}
    }
}

bool						Network::securiseConnection(Socket &client)
{
  RtypeProtocol::Data::Handshake		*syn_ack;

  syn_ack = new RtypeProtocol::Data::Handshake;
  if (client.getSyn() == -1 && client.getAck() == -1)
    {
      if (receiveMsg(client.getFdClient(), sizeof(RtypeProtocol::Data::Handshake)) == false)
	{
	  deleteSocket(client);
	  return false;
	}
      client.setSyn(reinterpret_cast<RtypeProtocol::Data::Handshake *>(this->msgReceived)->syn);
      syn_ack->code = RtypeProtocol::convertShort(RtypeProtocol::serverCodes::SYN_ACK);
      syn_ack->syn = reinterpret_cast<RtypeProtocol::Data::Handshake *>(this->msgReceived)->syn + 1;
      syn_ack->ack = rand() % 1000;
      if (sendMsg(client.getFdClient(), syn_ack, sizeof(syn_ack)) == false)
	{
	  delete syn_ack;
	  deleteSocket(client);
	  return false;
	}
    }
  else
    {
      if (receiveMsg(client.getFdClient(), sizeof(RtypeProtocol::Data::Handshake)) == false)
	{
	  delete syn_ack;
	  deleteSocket(client);
	  return false;
	}
      client.setAck(reinterpret_cast<RtypeProtocol::Data::Handshake *>(this->msgReceived)->ack);
      if (syn_ack->ack != client.getAck() + 1)
	{
	  std::cerr << "Handshake failed, closing connection..." << std::endl;
	  delete syn_ack;
	  deleteSocket(client);
	  return false;
	}
    }
  delete syn_ack;
  return true;
}
