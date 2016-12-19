//
// IAI.hpp for rtype in /home/rochon_k/rendu/rtype/server/include
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Tue Dec 13 19:43:17 2016 kevin rochon
// Last update Mon Dec 19 16:32:12 2016 kevin rochon
//

#ifndef IAI_HPP_
# define IAI_HPP_

# include "AComponent.hh"

class		IAI : public AComponent
{
 public:
  virtual void	update() = 0;
};

#endif /* !IAI_HPP_ */
