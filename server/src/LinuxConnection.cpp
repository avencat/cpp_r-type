//
// Network.cpp for Network in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Wed Dec 14 15:57:21 2016 Jessica VAN-DEN-ZANDE
// Last update Fri Dec 30 18:48:50 2016 Jessica VAN-DEN-ZANDE
//

#include "LinuxConnection.hpp"
#include "Configuration.hh"

Network::Network() {}

Network::~Network() {}


void				Network::addClient(const std::string ip, const int port)
{
  Client			newClient;
  std::list<Client>::iterator	it;

  newClient.setIp(ip);
  newClient.setPort(port);
  clients.push_back(newClient);
}

bool				Network::initServer(int port)
{
  this->servSocket = socket(AF_INET, SOCK_DGRAM, 0);
  bzero((char *) &servAddr, sizeof(servAddr));
  this->servAddr.sin_family = AF_INET;
  this->servAddr.sin_port = htons(port);
  this->servAddr.sin_addr.s_addr = INADDR_ANY;
  if (bind(this->servSocket, (struct sockaddr *) &(this->servAddr),
	   sizeof(this->servAddr)) == -1)
    {
      std::cerr << "Error on binding." << std::endl;
      return false;
    }
  return true;
}

bool					Network::runServer(bool stateServer)
{
  Configuration				config("config.ini", false);
  std::stringstream			ss;
  int					clientPort;
  std::list<Client>::iterator		it;

  clientLen = sizeof(clientAddr);
  while (stateServer == true)
    {
      bzero(this->msgReceived, 1024);
      clientLen = sizeof(clientAddr);
      if (recvfrom(this->servSocket, this->msgReceived, 1024, 0,
		   (struct sockaddr *)&clientAddr, &clientLen) < 0)
	std::cerr << "Error in recvfrom" << std::endl;
      clientPort = ntohs(clientAddr.sin_port);
      std::string clientIp(inet_ntoa(clientAddr.sin_addr));
      std::cout << "client ip : "<< clientIp << std::endl;
      if (std::find(clients.begin(), clients.end(), clientIp) == clients.end())	
	{
	  addClient(clientIp, clientPort);
	  config.addToWhitelist(clientIp);
	  std::cout << "add to client list and whitelist" << std::endl;
	}
      sendto(this->servSocket, "coucou\n", strlen("coucou\n"), 0, 
	     (struct sockaddr *)&clientAddr, clientLen);
    }
  return (false);
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
