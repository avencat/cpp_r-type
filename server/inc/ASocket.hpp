//
// ASocket.hpp for Socket in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Thu Dec 15 00:59:15 2016 Jessica VAN-DEN-ZANDE
// Last update Thu Dec 15 01:26:04 2016 Jessica VAN-DEN-ZANDE
//

#ifndef ASOCKET_HPP__
# define ASCKET_HPP__

# include <iostream>

class				ASocket
{
protected:
  int				fdClient;
  std::string			username;
public:
  ASocket();
  ~ASocket();
  virtual void			setUsername(const std::string name) = 0;
  virtual std::string		getUsername(void) const = 0;
  virtual void			setFdClient(int fd) = 0;
  virtual int			getFdClient(void) = 0;
};

#endif /* !ASOCKET_HPP__ */
