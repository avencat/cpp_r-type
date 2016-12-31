//
// Player.cpp for Player in /home/van-de_j/Tek3/rendu/RType/test_rtype
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Thu Dec 15 01:05:16 2016 Jessica VAN-DEN-ZANDE
// Last update Sat Dec 31 15:01:15 2016 Jessica VAN-DEN-ZANDE
//

#include "Player.hpp"

Player::Player(const AClient &client) : AClient(client)
{
  this->isInRoom = false;
  this->isReady = false;
  this->score = 0;
  this->lives = 3;
  this->powerup = 0;
}

Player::~Player() {}

void			Player::setIsReady(bool state)
{
  this->isReady = state;
}
bool			Player::getIsReady(void)
{
  return this->isReady;
}
void			Player::setScore(int nb)
{
  this->score = nb;
}
int			Player::getScore(void)
{
  return this->score;
}
void			Player::setLives(int nb)
{
  this->lives = nb;
}
int			Player::getLives(void)
{
  return this->lives;
}
void			Player::setPowerup(int nb)
{
  this->powerup = nb;
}
int			Player::getPowerup(void)
{
  return this->powerup;
}


bool			Player::operator==(const Player &client)
{
  return this->ip == client.getIp() && this->port == client.getPort();
}

bool			Player::operator==(const std::string &str)
{
  return this->ip == str;
}
