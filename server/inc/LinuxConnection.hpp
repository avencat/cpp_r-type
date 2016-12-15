//
// LinuxConnection.hpp for LinuxConnection in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Wed Dec 14 17:03:58 2016 Jessica VAN-DEN-ZANDE
// Last update Thu Dec 15 12:43:17 2016 Jessica VAN-DEN-ZANDE
//

#include "INetwork.hpp"
#include "Socket.hpp"

class Network : public INetwork
{
private:
  std::list<Socket>	clients;
  int			servSocket;
  int			fdMax;
  fd_set		listReadFd;
  fd_set		listWriteFd;
  struct timeval	timeout;
  struct sockaddr_in	serv_addr;
public:
  Network();
  ~Network();
  bool			initServer(int port, int queue);
  bool			runServer(bool stateServer);
  void			addSocket();
  void			deleteSocket(Socket toDelete);
  void			setReadList(void);
  void			setWriteList(void);
  void			checkActivity(void);
};
