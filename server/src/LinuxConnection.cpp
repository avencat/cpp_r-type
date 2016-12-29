//
// Network.cpp for Network in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Wed Dec 14 15:57:21 2016 Jessica VAN-DEN-ZANDE
// Last update Fri Dec 30 00:08:04 2016 Jessica VAN-DEN-ZANDE
//

#include "LinuxConnection.hpp"
#include "RtypeProtocol.hh"

Network::Network() 
{
  this->fdMax = 0;
}

Network::~Network() {}

bool		Network::sendMsg(int fdSocket, const char *msg, const size_t &dataSize)
{
  if (send(fdSocket, msg, dataSize, 0) == false)
    {
      std::cerr << "sendMsg() failed." << std::endl;
      return false;
    }
  return true;
}

bool		Network::receiveMsg(int fdSocket, const size_t &dataSize)
{
  int		rv;

  rv = recv(fdSocket, this->msgReceived, dataSize, 0);
  if (rv == -1)
    {
      std::cerr << strerror(errno) << std::endl;
      return false;
    }
  return true;
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

void				Network::deleteSocket(Socket &toDelete)
{
  std::list<Socket>::iterator	it;

  for (it = clients.begin(); it != clients.end();)
    {
      if (it->getFdClient() == toDelete.getFdClient())
	{
	  close(it->getFdClient());
	  it = clients.erase(it);
	  return;
	}
      ++it;
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

void				Network::checkActivity(void)
{
  std::list<Socket>::iterator	it;
  std::list<Socket>::iterator	tmp;
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
	      if (secureConnection(*it) == false)
		{
		  std::cerr << "Connection not secure, closing socket." << std::endl;
		  tmp = it;
		  it--;
		  deleteSocket(*tmp);
		}
	      else if (it->getSynState() == true && it->getAckState() == true)
		{
		  std::cout << "Connection is secure." << std::endl;
		} 
	    }
    	}
    }
}

bool						Network::secureConnection(Socket &client)
{
  RtypeProtocol::Data::Handshake		syn_ack;
  RtypeProtocol::Data::Code			code_handshake;
  unsigned long					size = sizeof(syn_ack.code) + sizeof(syn_ack.syn) + sizeof(syn_ack.ack);
  std::stringstream				ss;

  if (receiveMsg(client.getFdClient(), size) == false)
    {
      deleteSocket(client);
      return false;
    }
  ss.clear();
  ss.write(this->msgReceived, size);
  ss.read(reinterpret_cast<char*>(&(syn_ack.code)), sizeof(syn_ack.code));
  ss.read(reinterpret_cast<char*>(&(syn_ack.syn)), sizeof(syn_ack.syn));
  ss.read(reinterpret_cast<char*>(&(syn_ack.ack)), sizeof(syn_ack.ack));
  if (client.getSynState() == false && client.getAckState() == false)
    {
      client.setSyn(syn_ack.syn);
      client.setSynState(true);
      syn_ack.code = RtypeProtocol::convertShort(RtypeProtocol::serverCodes::SYN_ACK);
      ++syn_ack.syn;
      srand(time(NULL));
      syn_ack.ack = rand();
      client.setAck(syn_ack.ack);
      std::cout << "code : " << syn_ack.code << " syn : " << syn_ack.syn << " ack : " << syn_ack.ack << std::endl;
      ss.clear();
      ss.str("");
      ss.write(reinterpret_cast<char*>(&(syn_ack.code)), sizeof(syn_ack.code));
      ss.write(reinterpret_cast<char*>(&(syn_ack.syn)), sizeof(syn_ack.syn));
      ss.write(reinterpret_cast<char*>(&(syn_ack.ack)), sizeof(syn_ack.ack));
      if (this->sendMsg(client.getFdClient(), ss.str().c_str(), size) == false)
	{
	  deleteSocket(client);
	  return false;
	}
    }
  else
    {
      if (syn_ack.ack != client.getAck() + 1)
	{
	  std::cout << "stored ack: " << client.getAck() << std::endl;
	  std::cout << "syn_ack.ack send by client: " << syn_ack.ack << std::endl;
	  std::cerr << "Handshake failed..." << std::endl;
	  return false;
	}
      client.setAck(syn_ack.ack);
      client.setAckState(true);
      std::cout << "Send validation to client.\n" << std::endl;
      code_handshake.code = RtypeProtocol::convertShort(RtypeProtocol::serverCodes::Accepted);
      ss.clear();
      ss.str("");
      ss.write(reinterpret_cast<char*>(&(code_handshake.code)), sizeof(code_handshake.code));
      if (sendMsg(client.getFdClient(), ss.str().c_str(), sizeof(code_handshake)) == false)
      	{
      	  deleteSocket(client);
      	  return false;
      	}
      std::cout << "Connection securised.\n" << std::endl;
    }
  return true;
}
