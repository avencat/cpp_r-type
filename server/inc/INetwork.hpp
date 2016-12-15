//
// Network.hpp for INetwork in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Wed Dec 14 15:47:42 2016 Jessica VAN-DEN-ZANDE
// Last update Thu Dec 15 12:05:58 2016 Jessica VAN-DEN-ZANDE
//

#ifndef TEST_RTYPE_INETWORK_HPP
# define TEST_RTYPE_INETWORK_HPP

# include <iostream>
# include <list>
# include <unistd.h>
# include <sys/socket.h>
# include <string.h>
# include <arpa/inet.h>
# include <ctime>
# include <stdlib.h>
# include <sstream>
# include <string>

class INetwork
{
public:
  virtual ~INetwork() {};
  virtual bool initServer(int port, int queue) = 0;
};

#endif /* TEST_RTYPE_INETWORK_HPP */
