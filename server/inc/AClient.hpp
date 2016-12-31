//
// AClient.hpp for Client in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Thu Dec 15 00:59:15 2016 Jessica VAN-DEN-ZANDE
// Last update Sat Dec 31 15:45:47 2016 Jessica VAN-DEN-ZANDE
//

#ifndef ASOCKET_HPP__
# define ASOCKET_HPP__

# include <iostream>
# include <unistd.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <vector>

class				AClient
{
protected:
  std::string    		ip;
  int				port;
  std::string			username;
  struct sockaddr_in		clientAddr;
  std::vector<std::string>	msgQueue;
private:
  int				syn;
  int				ack;
  bool				synState;
  bool				ackState;
public:
  AClient();
  ~AClient();
  AClient(const AClient &);
  void			setIp(const std::string ip);
  std::string		getIp(void) const;
  void			setPort(const int port);
  int			getPort(void) const;
  void			setUsername(const std::string name);
  std::string		getUsername(void) const;
  void 			setSyn(int syn);
  int  			getSyn(void) const;
  void 			setAck(int ack);
  int  			getAck(void) const;
  void 			setSynState(bool state);
  bool 			getSynState(void) const;
  void 			setAckState(bool state);
  bool 			getAckState(void) const;
  void			setclientAddr(struct sockaddr_in &clientAddr);
  struct sockaddr_in    &getclientAddr(void);
  bool 			operator==(const AClient&);
  bool 			operator==(const std::string &);
};


#endif /* !ASOCKET_HPP__ */
