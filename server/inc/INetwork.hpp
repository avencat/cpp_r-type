//
// INetwork.hpp for INetwork in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Wed Dec 14 15:47:42 2016 Jessica VAN-DEN-ZANDE
// Last update Sat Dec 31 12:27:01 2016 Jessica VAN-DEN-ZANDE
//

#ifndef TEST_RTYPE_INETWORK_HPP
# define TEST_RTYPE_INETWORK_HPP

# include <iostream>
# include <list>
# include <unistd.h>
# include <sys/socket.h>
# include <string.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netdb.h>
# include <ctime>
# include <stdlib.h>
# include <sstream>
# include <string>
# include "Configuration.hh"

class INetwork
{
public:
  virtual ~INetwork() {};
  virtual bool initServer(int port) = 0;
  virtual bool runServer(bool stateServer, 
			 Configuration &config) = 0;
};

#endif /* TEST_RTYPE_INETWORK_HPP */
