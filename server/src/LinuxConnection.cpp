//
// Network.cpp for Network in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Wed Dec 14 15:57:21 2016 Jessica VAN-DEN-ZANDE
// Last update Sat Dec 31 16:00:08 2016 Jessica VAN-DEN-ZANDE
//

#include "LinuxConnection.hpp"

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

bool					Network::runServer(bool stateServer, 
							   Configuration &config)
{
  std::stringstream			ss;
  int					clientPort;
  int					rv;

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
      if (std::find(clients.begin(), clients.end(), clientIp) == clients.end())	
	{
	  addClient(clientIp, clientPort, clientAddr);
	  config.addToWhitelist(clientIp);
	  std::cout << "add to client list and whitelist" << std::endl;
	}
      sendMsg("Test.", clients.back().getclientAddr());
      //check si joueur n'est pas en game.
      analyzeMsg();
    }
  return (false);
}

void					Network::analyzeMsg()
{
  RtypeProtocol::Data::Code		code_send;
  unsigned long				size = sizeof(code_send.code);
  std::stringstream			ss;
  RtypeProtocol::clientCodes	       	code;

  ss.clear();
  ss.write(this->msgReceived, size);
  ss.read(reinterpret_cast<char*>(&(code_send.code)), sizeof(code_send.code));
  std::cout << "code is : " << code_send.code << std::endl;
  code = RtypeProtocol::convertClient(code_send.code);
  switch(code)
    {
    case RtypeProtocol::clientCodes::SYN:
      std::cout << "code handshake : SYN part" << std::endl;
      break;
    case RtypeProtocol::clientCodes::ACK:
      std::cout << "code handshake : ACK part" << std::endl;
      break;
    case RtypeProtocol::clientCodes::Ping:
      std::cout << "Ping" << std::endl;
      break;
    case RtypeProtocol::clientCodes::Username:
      std::cout << "Username" << std::endl;
      break;
    case RtypeProtocol::clientCodes::RoomJoin:
      std::cout << "RoomJoin" << std::endl;
      break;
    case RtypeProtocol::clientCodes::RoomCreate:
      std::cout << "RoomCreate" << std::endl;
      break;
    default:
      std::cout << "Uknow client code" << std::endl;
    }
}

// bool						Network::secureConnection(Socket &client)
// {
  // RtypeProtocol::Data::Handshake		syn_ack;
  // RtypeProtocol::Data::Code			code_handshake;
  // unsigned long					size = sizeof(syn_ack.code) + sizeof(syn_ack.syn) + sizeof(syn_ack.ack);
  // std::stringstream				ss;

//   if (receiveMsg(client.getFdClient(), size) == false)
//     {
//       deleteSocket(client);
//       return false;
//     }
//   ss.clear();
//   ss.write(this->msgReceived, size);
//   ss.read(reinterpret_cast<char*>(&(syn_ack.code)), sizeof(syn_ack.code));
//   ss.read(reinterpret_cast<char*>(&(syn_ack.syn)), sizeof(syn_ack.syn));
//   ss.read(reinterpret_cast<char*>(&(syn_ack.ack)), sizeof(syn_ack.ack));
//   if (client.getSynState() == false && client.getAckState() == false)
//     {
//       client.setSyn(syn_ack.syn);
//       client.setSynState(true);
//       syn_ack.code = RtypeProtocol::convertShort(RtypeProtocol::serverCodes::SYN_ACK);
//       ++syn_ack.syn;
//       srand(time(NULL));
//       syn_ack.ack = rand();
//       client.setAck(syn_ack.ack);
//       std::cout << "code : " << syn_ack.code << " syn : " << syn_ack.syn << " ack : " << syn_ack.ack << std::endl;
//       ss.clear();
//       ss.str("");
//       ss.write(reinterpret_cast<char*>(&(syn_ack.code)), sizeof(syn_ack.code));
//       ss.write(reinterpret_cast<char*>(&(syn_ack.syn)), sizeof(syn_ack.syn));
//       ss.write(reinterpret_cast<char*>(&(syn_ack.ack)), sizeof(syn_ack.ack));
//       if (this->sendMsg(client.getFdClient(), ss.str().c_str(), size) == false)
// 	{
// 	  deleteSocket(client);
// 	  return false;
// 	}
//     }
//   else
//     {
//       if (syn_ack.ack != client.getAck() + 1)
// 	{
// 	  std::cout << "stored ack: " << client.getAck() << std::endl;
// 	  std::cout << "syn_ack.ack send by client: " << syn_ack.ack << std::endl;
// 	  std::cerr << "Handshake failed..." << std::endl;
// 	  return false;
// 	}
//       client.setAck(syn_ack.ack);
//       client.setAckState(true);
//       std::cout << "Send validation to client.\n" << std::endl;
//       code_handshake.code = RtypeProtocol::convertShort(RtypeProtocol::serverCodes::Accepted);
//       ss.clear();
//       ss.str("");
//       ss.write(reinterpret_cast<char*>(&(code_handshake.code)), sizeof(code_handshake.code));
//       if (sendMsg(client.getFdClient(), ss.str().c_str(), sizeof(code_handshake)) == false)
//       	{
//       	  deleteSocket(client);
//       	  return false;
//       	}
//       std::cout << "Connection securised.\n" << std::endl;
//     }
//   return true;
// }
