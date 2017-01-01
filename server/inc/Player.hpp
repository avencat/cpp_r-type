//
// Player.hpp for client in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Thu Dec 15 01:05:37 2016 Jessica VAN-DEN-ZANDE
// Last update Sun Jan  1 22:38:20 2017 Jessica VAN-DEN-ZANDE
//

#ifndef PLAYER_HPP__
# define PLAYER_HPP__

# include "AClient.hpp"

class				Player : public AClient
{
private:
  int				score;
  int				lives;
  int				powerup;
  bool				isReady;
  std::vector<std::string>	msg;	

public:
  Player(AClient &);
  ~Player();
  void				setIsReady(const bool state);
  bool				getIsReady(void) const;
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
