//
// AClient.hpp for Client in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Thu Dec 15 00:59:15 2016 Jessica VAN-DEN-ZANDE
// Last update Sun Jan  1 16:55:39 2017 Jessica VAN-DEN-ZANDE
//

#ifndef ACLIENT_HPP__
# define ACLIENT_HPP__

# include <iostream>
# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <vector>

class				AClient
{
public:
  enum				State
    {
      NEW = 0,
      SYN,
      ACK,
      USERNAME,
    };
protected:
  std::string    		ip;
  int				port;
  std::string			username;
  struct sockaddr_in		clientAddr;
  bool				isInRoom;
  std::vector<std::string>	msgQueue;
private:
  State				state;
  int				syn;
  int				ack;
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
  void			setState(const State &state);
  const State  		&getState() const;
  std::vector<std::string>	&getMsgQueue();
  void			setclientAddr(struct sockaddr_in &clientAddr);
  struct sockaddr_in    &getclientAddr(void);
  void			setIsInRoom(bool state);
  bool			getIsInRoom();
  void			addMsgInQueue(const std::string &msg);
  bool 			operator==(const AClient&);
  bool 			operator==(const std::string &);
  bool			operator==(const struct sockaddr_in &client);
};


#endif /* !ASOCKET_HPP__ */
