//
// AClient.hpp for Client in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Thu Dec 15 00:59:15 2016 Jessica VAN-DEN-ZANDE
// Last update Sat Dec 31 10:28:50 2016 Jessica VAN-DEN-ZANDE
//

#ifndef ASOCKET_HPP__
# define ASOCKET_HPP__

# include <iostream>
# include <unistd.h>
# include <sys/socket.h>

class				AClient
{
protected:
  std::string    		ip;
  int				port;
  std::string			username;
  // struct sockaddr_in		clientAddr;
public:
  AClient();
  ~AClient();
  virtual void			setIp(const std::string ip) = 0;
  virtual std::string		getIp(void) const = 0;
  virtual void			setPort(const int port) = 0;
  virtual int			getPort(void) const = 0;
  virtual void			setUsername(const std::string name) = 0;
  virtual std::string		getUsername(void) const = 0;
  // virtual void			setclientAddr(struct sockaddr_in &clientAddr) = 0;
  // virtual struct sockaddr_in    getclientAddr(void) = 0;
  bool				operator==(const AClient&);
  bool				operator==(const std::string &);
};


#endif /* !ASOCKET_HPP__ */
