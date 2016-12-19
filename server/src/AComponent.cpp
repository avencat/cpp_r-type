//
// AComponent.cpp for rtype in /home/rochon_k/rendu/rtype/server/src
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Mon Dec 19 15:16:05 2016 kevin rochon
// Last update Mon Dec 19 17:19:45 2016 kevin rochon
//

#include "AComponent.hh"

AComponent::AComponent(const int id) : _id(id)
{

}

AComponent::~AComponent()
{

}

int	AComponent::getId() const
{
  return (this->_id);
}

void	AComponent::setId(int id)
{
  this->_id = id;
}
