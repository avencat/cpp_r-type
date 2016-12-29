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

AComponent::AComponent(const Type &id) : _id(id)
{

}

AComponent::~AComponent()
{

}

const AComponent::Type	&AComponent::getId() const
{
  return (this->_id);
}

void	AComponent::setId(const Type &id)
{
  this->_id = id;
}
