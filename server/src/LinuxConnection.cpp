//
// Network.cpp for Network in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Wed Dec 14 15:57:21 2016 Jessica VAN-DEN-ZANDE
// Last update Sun Jan  1 23:46:50 2017 Maxime BOUCHER
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

bool					Network::runServer(const bool stateServer, 
							   Configuration &config)
{
  std::stringstream			ss;
  int					clientPort;
  std::list<AClient>::iterator		it;

  this->tickrate = std::stoi(config.getConfigKey("tickrate"), nullptr, 0);
  core.initRooms(this->tickrate);
  clientLen = sizeof(clientAddr);
  while (stateServer == true)
    {
      bzero(this->msgReceived, 1024);
      clientLen = sizeof(clientAddr);
      core.checkRooms();
      rv = recvfrom(this->servSocket, this->msgReceived, 1024, 0,
		    (struct sockaddr *)&clientAddr, &clientLen);
      if (rv < 0)
	std::cerr << "Error in recvfrom()" << std::endl;
      else if (rv == 0)
	std::cout << "client quit." << std::endl;
      clientPort = ntohs(clientAddr.sin_port);
      std::string clientIp(inet_ntoa(clientAddr.sin_addr));
      if (std::find(clients.begin(), clients.end(), clientAddr) == clients.end())	
	{
	  addClient(clientIp, clientPort, clientAddr);
	  config.addToWhitelist(clientIp);
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
  syn_ack.code = RtypeProtocol::convertShort(RtypeProtocol::serverCodes::SYN_ACK);
  ++syn_ack.syn;
  srand(time(NULL));
  syn_ack.ack = rand() % 1000;
  client.setAck(syn_ack.ack);
  ss.clear();
  ss.str("");
  ss.write(reinterpret_cast<char*>(&(syn_ack.code)), sizeof(syn_ack.code));
  ss.write(reinterpret_cast<char*>(&(syn_ack.syn)), sizeof(syn_ack.syn));
  ss.write(reinterpret_cast<char*>(&(syn_ack.ack)), sizeof(syn_ack.ack));
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
      sendCode(RtypeProtocol::serverCodes::ErrConnectionFailure, client);
      deleteClient(client);
      return;
    }
  client.setAck(syn_ack.ack);
  client.setState(AClient::State::ACK);
  sendCode(RtypeProtocol::serverCodes::Accepted, client);
}

void					Network::doPong(AClient &client)
{
  std::stringstream			ss;
  RtypeProtocol::Data::Code		pong;

  ss.clear();
  ss.str("");
  sendCode(RtypeProtocol::serverCodes::Pong, client);
}

void					Network::sendRoomList(AClient &client)
{
  std::list<Room *>::iterator  		it;
  std::stringstream			ss;
  RtypeProtocol::Data::RoomBegin	roomBegin;
  RtypeProtocol::Data::Room		room;
  ss.clear();
  ss.str("");
  roomBegin.code = RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomList);
  roomBegin.tickrate = tickrate;
  ss.write(reinterpret_cast<char*>(&(roomBegin.code)), sizeof(roomBegin.code));
  ss.write(reinterpret_cast<char*>(&(roomBegin.tickrate)), sizeof(roomBegin.tickrate));  
  sendMsg(ss.str(), client.getclientAddr());
  for (it = core.getListRoom().begin(); it != core.getListRoom().end(); it++)
    {
      ss.clear();
      ss.str("");
      room.code = RtypeProtocol::convertShort(RtypeProtocol::serverCodes::Room);
      room.roomID = (*it)->getId();
      room.players = static_cast<char>((*it)->getNbPlayer());
      room.state = static_cast<RtypeProtocol::roomState>((*it)->getState());
      ss.write(reinterpret_cast<char*>(&(room.code)), sizeof(room.code));
      ss.write(reinterpret_cast<char*>(&(room.roomID)), sizeof(room.roomID));
      ss.write(reinterpret_cast<char*>(&(room.players)), sizeof(room.players));
      ss.write(reinterpret_cast<char*>(&(room.state)), sizeof(room.state));
      sendMsg(ss.str(), client.getclientAddr());
    }
  sendCode(RtypeProtocol::serverCodes::RoomListEnd, client);
}

void					Network::checkUsername(AClient &client)
{
  std::stringstream			ss;
  RtypeProtocol::Data::Code		code;
  RtypeProtocol::Data::Username		username;
  unsigned long				size = sizeof(username.code) + sizeof(username.username);
  std::string	       			name;
  std::list<Room *>			room;

  room = core.getListRoom();
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
  if (name.length() < 2 || name.length() > 12)
    {
      sendCode(RtypeProtocol::serverCodes::ErrInvalidName, client);
      deleteClient(client);
      return;
    }
  client.setState(AClient::State::USERNAME);
  sendRoomList(client);
  }

bool					Network::checkRoomAvaibility(AClient &client, 
								     Room *room)
{
  std::stringstream			ss;
  RtypeProtocol::Data::Code		code;

  if (room->getState() == inGame)
    {
      sendCode(RtypeProtocol::serverCodes::ErrAlreadyStarted, client);
      return false;
    }
  if (room->getNbPlayer() == 4)
    {
      sendCode(RtypeProtocol::serverCodes::ErrPlayerLimit, client);
      return false;
    }
  return true;
}

void					Network::createRoom(AClient &client, int id)
{
  std::list<Room *>::iterator		it;
  std::stringstream			ss;
  RtypeProtocol::Data::RoomCreation    	newRoom;
  std::list<Room *>			room;

  ss.clear();
  ss.str("");
  newRoom.code = RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomCreated);
  newRoom.id = core.activateRoom(id);
  ss.write(reinterpret_cast<char*>(&(newRoom.code)), sizeof(newRoom.code));
  ss.write(reinterpret_cast<char*>(&(newRoom.id)), sizeof(newRoom.id));  
  sendMsg(ss.str(), client.getclientAddr());
  checkJoinRoom(client, true);
  room = core.getListRoom();
}

void					Network::checkCreateRoom(AClient &client)
{
  std::list<Room *>::iterator		it;
  std::stringstream			ss;
  RtypeProtocol::Data::RoomCreation    	newRoom;
  unsigned long				size = sizeof(newRoom.code) + sizeof(newRoom.id);

  if (static_cast<unsigned long>(rv) != size)
    {
      sendCode(RtypeProtocol::serverCodes::ErrIDConflict, client);
      deleteClient(client);
      return;
    }
  ss.clear();
  ss.str("");
  ss.write(this->msgReceived, size);
  ss.read(reinterpret_cast<char*>(&(newRoom.code)), sizeof(newRoom.code));
  ss.read(reinterpret_cast<char*>(&(newRoom.id)), sizeof(newRoom.id));
  for (it = core.getListRoom().begin(); it != core.getListRoom().end(); it++)
    {
      if ((*it)->getId() == newRoom.id)
	{
	  sendCode(RtypeProtocol::serverCodes::ErrIDConflict, client);
	  return;
	}
    }
  createRoom(client, newRoom.id);
}

void					Network::checkJoinRoom(AClient &client, bool avoid)
{
  std::vector<std::string>		playerName;
  std::list<Room *>::iterator		it;
  std::stringstream			ss;
  RtypeProtocol::Data::Code		code;
  RtypeProtocol::Data::RoomJoin		roomJoin;
  RtypeProtocol::Data::RoomJoined	roomJoined;
  unsigned long				size = sizeof(roomJoin.code) + sizeof(roomJoin.id) + sizeof(roomJoin.mode);

  if (static_cast<unsigned long>(rv) != size && avoid == false)
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
  for (it = core.getListRoom().begin(); it != core.getListRoom().end(); it++)
    {
      if ((*it)->getId() == roomJoin.id)
	{
	  if (checkRoomAvaibility(client, *it) == true)
	    {
	      playerName = core.addPlayerInRoom(client, roomJoin.id);
	      ss.clear();
	      ss.str("");
	      
	      roomJoined.code = RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomJoined);
	      roomJoined.id = roomJoin.id;
	      ss.write(reinterpret_cast<char*>(&(roomJoined.code)), sizeof(roomJoined.code));
	      ss.write(reinterpret_cast<char*>(&(roomJoined.id)), sizeof(roomJoined.id));
	      size_t s;
	      for (size_t size = 0; size < 4; size++)
		{
		  s = 0;
		  if (playerName.size())
		    {
		      ss.write(playerName[0].c_str(), playerName[0].size());	       
		      s = playerName[0].size();
		      playerName.erase(playerName.begin());
		    }
		  for (size_t i = 0; i < 12 - s; ++i)
		    {
		      ss.put(0);
		    }
		}
	      sendMsg(ss.str(), client.getclientAddr());
	      return;
	    }
	}
    }
  createRoom(client, roomJoin.id);
}

void					Network::sendCode(const RtypeProtocol::Data::Code &code, AClient &client)
{
  std::stringstream			ss;
  short					c;

  c = code.code;
  ss.clear();
  ss.str("");
  ss.write(reinterpret_cast<char*>(&(c)), sizeof(c));
  sendMsg(ss.str(), client.getclientAddr());
}

void					Network::analyzeMsg(const struct sockaddr_in &client)
{
  RtypeProtocol::Data::Code		code_send;
  unsigned long				size = sizeof(code_send.code);
  std::stringstream			ss;
  RtypeProtocol::clientCodes	       	code;
  std::list<AClient>::iterator		it;
  std::list<Room *>			room;

  room = core.getListRoom();
  it = std::find(clients.begin(), clients.end(), client);
  ss.clear();
  ss.str("");
  ss.write(this->msgReceived, size);
  ss.read(reinterpret_cast<char*>(&(code_send.code)), sizeof(code_send.code));
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
	    checkJoinRoom(*it, false);
	    break;
	  case RtypeProtocol::clientCodes::RoomCreate:
	    checkCreateRoom(*it);
	    break;
	  default:
	    {
	      ss.clear();
	      ss.str("");
	      sendCode(RtypeProtocol::serverCodes::ErrNotFound, *it);
	    }
	    
	  }
      }
    }
}
