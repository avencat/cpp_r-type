//
// Player.hpp for client in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Thu Dec 15 01:05:37 2016 Jessica VAN-DEN-ZANDE
// Last update Thu Dec 15 11:42:57 2016 Jessica VAN-DEN-ZANDE
//

#ifndef SOCKET_HPP__
# define SOCKET_HPP__

# include "ASocket.hpp"

class			Socket : public ASocket
{
private:
  bool			isReady;
  int			score;
  int			lives;
  int			powerup;
public:
  Socket();
  ~Socket();
  void			setIsReady(bool state);
  bool			getIsReady(void);
  void			setScore(int nb);
  int			getScore(void);
  void			setLives(int nb);
  int			getLives(void);
  void			setPowerup(int nb);
  int			getPowerup(void);
  virtual void		setUsername(const std::string name);
  virtual std::string	getUsername(void) const;
  virtual void		setFdClient(int fd);
  virtual int		getFdClient(void);
};

#endif /* !SOCKET_HPP__ */
