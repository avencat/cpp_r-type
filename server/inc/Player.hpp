//
// Player.hpp for client in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Thu Dec 15 01:05:37 2016 Jessica VAN-DEN-ZANDE
// Last update Sat Dec 31 15:01:54 2016 Jessica VAN-DEN-ZANDE
//

#ifndef PLAYER_HPP__
# define PLAYER_HPP__

# include "AClient.hpp"

class			Player : public AClient
{
private:
  bool			isInRoom;
  bool			isReady;
  int			score;
  int			lives;
  int			powerup;

public:
  Player(const AClient &);
  ~Player();
  void				setIsReady(bool state);
  bool				getIsReady(void);
  void				setScore(int nb);
  int				getScore(void);
  void				setLives(int nb);
  int				getLives(void);
  void				setPowerup(int nb);
  int				getPowerup(void);
  bool				operator==(const Player&);
  bool				operator==(const std::string &);

};

#endif /* !PLAYER_HPP__ */