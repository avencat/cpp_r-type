//
// LinuxConnection.hpp for LinuxConnection in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Wed Dec 14 17:03:58 2016 Jessica VAN-DEN-ZANDE
// Last update Sat Dec 31 22:04:47 2016 Jessica VAN-DEN-ZANDE
//

#ifndef LINUXCONNECTION_HPP__
# define LINUXCONNECTION_HPP__

# include <cerrno>
# include <iostream>
# include <string>
# include <sstream>
# include <exception>
# include <stdexcept>
# include "INetwork.hpp"
# include "Player.hpp"
# include "RtypeProtocol.hh"
# include "Configuration.hh"

class Network: public INetwork
{
private:
  std::list<AClient>		clients;
  int				servSocket;
  socklen_t	       		clientLen;
  struct sockaddr_in		servAddr; // use to identifiate the client
  struct sockaddr_in		clientAddr;
  int				rv;
  char				msgReceived[1024];
public:
  Network();
  ~Network();
  bool				initServer(const int port);
  bool				runServer(bool stateServer, Configuration &config);
  void				addClient(const std::string &ip, const int port, 
					  struct sockaddr_in &clientAddr);
  void				deleteClient(const AClient &toDelete);
  bool				sendMsg(const std::string &msg,
					struct sockaddr_in &clientAddr);
  bool				checkClientState(const struct sockaddr_in &client);
  void				sendCode(const RtypeProtocol::Data::Code &c,
					 AClient &client);
  void				analyzeMsg(const struct sockaddr_in &clientAddr);
  void				checkSyn(AClient &client);
  void				checkAck(AClient &client);
  void				doPong(AClient &client);
//bool				secureConnection(Socket &client);
};

class	ClientNotFoundException : public std::runtime_error
{
private:
  std::string			ip;
  std::stringstream		ss;
public:
  ClientNotFoundException(const std::string &ip);
  virtual const char *what() throw();
  std::string		&getIp();
};

#endif /* !LINUXCONNECTION_HPP__ */
