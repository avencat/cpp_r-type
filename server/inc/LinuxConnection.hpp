//
// LinuxConnection.hpp for LinuxConnection in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Wed Dec 14 17:03:58 2016 Jessica VAN-DEN-ZANDE
// Last update Mon Dec 19 18:42:57 2016 Jessica VAN-DEN-ZANDE
//

#ifndef LINUXCONNECTION_HPP__
# define LINUXCONNECTION_HPP__

# include "../inc/INetwork.hpp"
# include "../inc/Socket.hpp"

class Network : public INetwork
{
private:
  std::list<Socket>		clients;
  int				servSocket;
  int				fdMax;
  fd_set			listReadFd;
  fd_set			listWriteFd;
  struct timeval		timeout;
  struct sockaddr_in		serv_addr;
  void				*msgReceived;
public:
  Network();
  ~Network();
  bool				initServer(int port, int queue);
  bool				runServer(bool stateServer);
  bool				sendMsg(int fdSocket, void *msgToSend, 
					const size_t &dataSize);
  bool				receiveMsg(int fdSocket, const size_t &dataSize);
  void				addSocket(void);
  void				deleteSocket(Socket toDelete);
  void				setReadList(void);
  void				setWriteList(void);
  void				checkActivity(void);
  bool				securiseConnection(Socket &client);
};

#endif /* !LINUXCONNECTION_HPP__ */
