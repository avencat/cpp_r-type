//
// AComponent.hpp for rtype in /home/rochon_k/rendu/rtype/server/inc
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Sun Dec 18 00:53:03 2016 kevin rochon
// Last update Mon Dec 19 07:46:15 2016 kevin rochon
//

#ifndef ACOMPONENT_HPP_
# define ACOMPONENT_HPP_

class	AComponent
{
 protected:
  int	_id;

 public:
  AComponent(const int id): _id(id) {};
  virtual ~AComponent() {};
};

#endif /* !ACOMPONENT_HPP_ */
