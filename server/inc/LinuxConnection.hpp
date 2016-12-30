//
// LinuxConnection.hpp for LinuxConnection in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Wed Dec 14 17:03:58 2016 Jessica VAN-DEN-ZANDE
// Last update Fri Dec 30 18:27:21 2016 Jessica VAN-DEN-ZANDE
//

#ifndef LINUXCONNECTION_HPP__
# define LINUXCONNECTION_HPP__

# include <cerrno>
# include <cstring>
# include <sstream>
# include "INetwork.hpp"
# include "Client.hpp"
# include "RtypeProtocol.hh"
# include "Configuration.hh"

class Network: public INetwork
{
private:
  std::list<Client>		clients;
  int				servSocket;
  socklen_t	       		clientLen;
  struct sockaddr_in		servAddr;
  struct sockaddr_in		clientAddr;
  char				msgReceived[1024];
public:
  Network();
  ~Network();
  bool				initServer(int port);
  bool				runServer(bool stateServer);
  void				addClient(const std::string ip, const int port);
//bool				secureConnection(Socket &client);
};

#endif /* !LINUXCONNECTION_HPP__ */
