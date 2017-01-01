//
// Network.cpp for Network in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Wed Dec 14 15:57:21 2016 Jessica VAN-DEN-ZANDE
// Last update Sun Jan  1 11:23:36 2017 Jessica VAN-DEN-ZANDE
//

#include "LinuxConnection.hpp"

ClientNotFoundException::ClientNotFoundException(const std::string &_ip) : runtime_error("Client not found"), ip(_ip)
{}

const char *ClientNotFoundException::what() const throw()
{
  return ((std::string(std::runtime_error::what()) + ": ip - " + ip).c_str());
}

const std::string &ClientNotFoundException::getIp() const
{
    return ip;
}

void    ClientNotFoundException::setIp(const std::string &_ip)
{
    ip = _ip;
}

Network::Network() {}

Network::~Network() {}

void				Network::deleteClient(const AClient &toDelete)
{
  std::list<AClient>::iterator	it;

  if ((it = std::find(clients.begin(), clients.end(), toDelete)) != clients.end())
    clients.erase(it);
}

void				Network::addClient(const std::string &ip, const int port,
						   struct sockaddr_in &clientAddr)
{
  AClient			newClient;

  newClient.setIp(ip);
  newClient.setPort(port);
  newClient.setclientAddr(clientAddr);
  clients.push_back(newClient);
}

bool				Network::initServer(const int port)
{
  this->servSocket = socket(AF_INET, SOCK_DGRAM, 0);
  bzero((char *) &servAddr, sizeof(servAddr));
  this->servAddr.sin_family = AF_INET;
  this->servAddr.sin_port = htons(port);
  this->servAddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(this->servSocket, (struct sockaddr *)&(this->servAddr),
	   sizeof(this->servAddr)) == -1)
    {
      std::cerr << "Error on binding." << std::endl;
      return false;
    }
  return true;
}

bool					Network::sendMsg(const std::string &msgToSend, 
							 struct sockaddr_in &clientAddr)
{
  int					rv;
  size_t				clientAddrSize;

  clientAddrSize = sizeof(clientAddr);

  for (size_t i = 0; i < msgToSend.length(); ++i)
    std::cout << "Msg[" << i << "]: " << static_cast<int>(static_cast<unsigned char>(msgToSend[i])) << std::endl;

  rv = sendto(this->servSocket, msgToSend.c_str(), msgToSend.length(), 0,
	      (struct sockaddr *)&clientAddr, clientAddrSize);
  if (rv == -1)
    {
      std::cerr << "sendMsg() failed" << std::endl;
      return false;
    }
  return true;
}

bool					Network::checkClientState(const struct sockaddr_in &client)
{
  std::list<AClient>::iterator		it;

  if ((it = std::find(clients.begin(), clients.end(), client)) != clients.end())
    {
      if (it->getIsInRoom() == false)
	return true;
      else
	it->addMsgInQueue(msgReceived);
      return false;
    }
  throw ClientNotFoundException(inet_ntoa(client.sin_addr));
}

bool					Network::runServer(bool stateServer, 
							   Configuration &config)
{
  std::stringstream			ss;
  int					clientPort;
  std::list<AClient>::iterator		it;

  clientLen = sizeof(clientAddr);
  while (stateServer == true)
    {
      bzero(this->msgReceived, 1024);
      clientLen = sizeof(clientAddr);
      rv = recvfrom(this->servSocket, this->msgReceived, 1024, 0,
		    (struct sockaddr *)&clientAddr, &clientLen);
      if (rv < 0)
	std::cerr << "Error in recvfrom()" << std::endl;
      else if (rv == 0)
	std::cout << "client quit." << std::endl;
      clientPort = ntohs(clientAddr.sin_port);
      std::string clientIp(inet_ntoa(clientAddr.sin_addr));
      std::cout << "client ip : "<< clientIp << " , port : " << clientPort << std::endl;
      if (std::find(clients.begin(), clients.end(), clientAddr) == clients.end())	
	{
	  addClient(clientIp, clientPort, clientAddr);
	  config.addToWhitelist(clientIp);
	  std::cout << "add to client list and whitelist" << std::endl;
	}
      try
	{
        if (checkClientState(clientAddr) == true) {
          analyzeMsg(clientAddr);
      }
    }
      catch (ClientNotFoundException &e)
	{
	  std::cerr << e.what() << std::endl;
	}
    }
  return (false);
}

void					Network::checkSyn(AClient &client)
{
  RtypeProtocol::Data::Handshake       	syn_ack;
  RtypeProtocol::Data::Code		code;
  std::stringstream			ss;
  unsigned long				size = sizeof(syn_ack.code) + sizeof(syn_ack.syn) + sizeof(syn_ack.ack);

  if (static_cast<unsigned long>(rv) != size)
    {
      sendCode(RtypeProtocol::serverCodes::ErrConnectionFailure, client);
      deleteClient(client);
      return;
    }
  ss.clear();
  ss.str("");
  ss.write(this->msgReceived, size);
  ss.read(reinterpret_cast<char*>(&(syn_ack.code)), sizeof(syn_ack.code));
  ss.read(reinterpret_cast<char*>(&(syn_ack.syn)), sizeof(syn_ack.syn));
  ss.read(reinterpret_cast<char*>(&(syn_ack.ack)), sizeof(syn_ack.ack));
  client.setSyn(syn_ack.syn);
  client.setState(AClient::State::SYN);
  std::cout << "syn : " << syn_ack.syn << std::endl;
  syn_ack.code = RtypeProtocol::convertShort(RtypeProtocol::serverCodes::SYN_ACK);
  ++syn_ack.syn;
  srand(time(NULL));
  syn_ack.ack = rand() % 1000;
  std::cout << "syn + 1 : " << syn_ack.syn << std::endl;
  std::cout << "ack : " << syn_ack.ack << std::endl;
  client.setAck(syn_ack.ack);
  ss.clear();
  ss.str("");
  ss.write(reinterpret_cast<char*>(&(syn_ack.code)), sizeof(syn_ack.code));
  ss.write(reinterpret_cast<char*>(&(syn_ack.syn)), sizeof(syn_ack.syn));
  ss.write(reinterpret_cast<char*>(&(syn_ack.ack)), sizeof(syn_ack.ack));
  std::cout << "code renvoyé : " << syn_ack.code << "\nsyn renvoyé : " << syn_ack.syn 
	    << "\nack renvoyé : " << syn_ack.ack <<std::endl;
  sendMsg(ss.str(), client.getclientAddr());
}

void					Network::checkAck(AClient &client)
{
  RtypeProtocol::Data::Handshake       	syn_ack;
  RtypeProtocol::Data::Code		code;
  std::stringstream			ss;
  unsigned long				size = sizeof(syn_ack.code) + sizeof(syn_ack.syn) + sizeof(syn_ack.ack);

  if (static_cast<unsigned long>(rv) != size)
    {
      sendCode(RtypeProtocol::serverCodes::ErrConnectionFailure, client);
      deleteClient(client);
      return;
    }
  ss.clear();
  ss.str("");
  ss.write(this->msgReceived, size);
  ss.read(reinterpret_cast<char*>(&(syn_ack.code)), sizeof(syn_ack.code));
  ss.read(reinterpret_cast<char*>(&(syn_ack.syn)), sizeof(syn_ack.syn));
  ss.read(reinterpret_cast<char*>(&(syn_ack.ack)), sizeof(syn_ack.ack));
  if (syn_ack.ack != client.getAck() + 1)
    {
      std::cout << "stored ack: " << client.getAck() << std::endl;
      std::cout << "syn_ack.ack send by client: " << syn_ack.ack << std::endl;
      std::cerr << "Handshake failed..." << std::endl;
      deleteClient(client);
      return;
    }
  client.setAck(syn_ack.ack);
  client.setState(AClient::State::ACK);
  std::cout << "Send validation to client.\n" << std::endl;
  sendCode(RtypeProtocol::serverCodes::Accepted, client);
  std::cout << "Connection securised.\n" << std::endl;
}

void					Network::doPong(AClient &client)
{
  std::stringstream			ss;
  RtypeProtocol::Data::Code		pong;

  ss.clear();
  ss.str("");
  sendCode(RtypeProtocol::serverCodes::Pong, client);
}

void					Network::checkUsername(AClient &client)
{
  std::stringstream			ss;
  RtypeProtocol::Data::Code		code;
  RtypeProtocol::Data::Username		username;
  unsigned long				size = sizeof(username.code) + sizeof(username.username);
  std::string	       			name;

  if (static_cast<unsigned long>(rv) != size)
    {
      sendCode(RtypeProtocol::serverCodes::ErrInvalidName, client);
      deleteClient(client);
      return;
    }
  ss.clear();
  ss.str("");
  ss.write(this->msgReceived, size);
  ss.read(reinterpret_cast<char*>(&(username.code)), sizeof(username.code));
  ss.read(reinterpret_cast<char*>(&(username.username)), sizeof(username.username));
  name = username.username;
  if (name.length() < 2)
    {
      sendCode(RtypeProtocol::serverCodes::ErrInvalidName, client);
      deleteClient(client);
      return;
    }
  client.setState(AClient::State::USERNAME);
  //function return tickrate + list room (one by one) + code end list
  sendCode(RtypeProtocol::serverCodes::Accepted, client);
}

void					Network::checkJoinRoom(AClient &client)
{
  std::stringstream			ss;
  RtypeProtocol::Data::Code		code;
  RtypeProtocol::Data::RoomJoin		roomJoin;
  unsigned long				size = sizeof(roomJoin.code) + sizeof(roomJoin.id) + sizeof(roomJoin.mode);

  if (static_cast<unsigned long>(rv) != size)
    {
      sendCode(RtypeProtocol::serverCodes::ErrIDConflict, client);
      deleteClient(client);
      return;
    }
  ss.clear();
  ss.str("");
  ss.write(this->msgReceived, size);
  ss.read(reinterpret_cast<char*>(&(roomJoin.code)), sizeof(roomJoin.code));
  ss.read(reinterpret_cast<char*>(&(roomJoin.id)), sizeof(roomJoin.id));  
  ss.read(reinterpret_cast<char*>(&(roomJoin.mode)), sizeof(roomJoin.mode));
}

void					Network::sendCode(const RtypeProtocol::Data::Code &code, AClient &client)
{
  std::stringstream			ss;
  short					c;

  c = code.code;
  ss.clear();
  ss.str("");
  ss.write(reinterpret_cast<char*>(&(c)), sizeof(c));
  std::cout << "sendCode() = " << code.code << std::endl;
  sendMsg(ss.str(), client.getclientAddr());
  std::cout << "code sent" << std::endl;
}

void					Network::analyzeMsg(const struct sockaddr_in &client)
{
  RtypeProtocol::Data::Code		code_send;
  unsigned long				size = sizeof(code_send.code);
  std::stringstream			ss;
  RtypeProtocol::clientCodes	       	code;
  std::list<AClient>::iterator		it;

  it = std::find(clients.begin(), clients.end(), client);
  ss.clear();
  ss.write(this->msgReceived, size);
  ss.read(reinterpret_cast<char*>(&(code_send.code)), sizeof(code_send.code));
  std::cout << "code is : " << code_send.code << std::endl;
  code = RtypeProtocol::convertClient(code_send.code);
  switch(it->getState())
    {
    case AClient::State::NEW:
      if (code != RtypeProtocol::clientCodes::SYN)
	{
	  sendCode(RtypeProtocol::serverCodes::ErrNotAuthenticated, *it);
	  deleteClient(*it);
	}
      else
	checkSyn(*it);	  
      break;
    case AClient::State::SYN:
      if (code != RtypeProtocol::clientCodes::ACK)
	{
	  sendCode(RtypeProtocol::serverCodes::ErrNotAuthenticated, *it);
	  deleteClient(*it);
	}
      else
	checkAck(*it);
      break;
    case AClient::State::ACK:
      if (code != RtypeProtocol::clientCodes::Username)
	{
	  sendCode(RtypeProtocol::serverCodes::ErrNotAuthenticated, *it);
	  deleteClient(*it);
	}
      else
	checkUsername(*it);
      break;
    case AClient::State::USERNAME:
      {
	switch(code)
	  {
	  case RtypeProtocol::clientCodes::Ping:
	    doPong(*it);
	    break;
	  case RtypeProtocol::clientCodes::RoomJoin:
	    std::cout << "RoomJoin" << std::endl;
	    break;
	  case RtypeProtocol::clientCodes::RoomCreate:
	    std::cout << "RoomCreate" << std::endl;
	    break;
	  default:
	    {
	      ss.clear();
	      ss.str("");
	      std::cout << "Code [: " << code << "] not found" << std::endl;
	      sendCode(RtypeProtocol::serverCodes::ErrNotFound, *it);
	    }
	    
	  }
      }
    }
}
