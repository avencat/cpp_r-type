//
// Player.hpp for client in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Thu Dec 15 01:05:37 2016 Jessica VAN-DEN-ZANDE
// Last update Sat Dec 31 10:28:24 2016 Jessica VAN-DEN-ZANDE
//

#ifndef CLIENT_HPP__
# define CLIENT_HPP__

# include "AClient.hpp"

class			Client : public AClient
{
private:
  bool			isReady;
  int			score;
  int			lives;
  int			powerup;
  int			syn;
  int			ack;
  bool			synState;
  bool			ackState;
public:
  Client();
  ~Client();
  void				setIsReady(bool state);
  bool				getIsReady(void);

  void				setScore(int nb);
  int				getScore(void);

  void				setLives(int nb);
  int				getLives(void);

  void				setPowerup(int nb);
  int				getPowerup(void);

  void				setSyn(int syn);
  int				getSyn(void) const;

  void				setAck(int ack);
  int				getAck(void) const;

  void				setSynState(bool state);
  bool				getSynState(void) const;

  void				setAckState(bool state);
  bool				getAckState(void) const;

  bool				operator==(const Client&);
  bool				operator==(const std::string &);

  virtual void			setUsername(const std::string name);
  virtual std::string		getUsername(void) const;

  virtual void			setIp(const std::string name);
  virtual std::string		getIp(void) const;

  virtual void			setPort(const int port);
  virtual int			getPort(void) const;

  // virtual void			setclientAddr(struct sockaddr_in clientAddr);
  // virtual struct sockaddr_in    getclientAddr(void);

};

#endif /* !SOCKET_HPP__ */
