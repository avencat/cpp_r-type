//
// AComponent.hh for rtype in /home/rochon_k/rendu/rtype/server/inc
//
// Made by kevin rochon
// Login   <rochon_k@epitech.net>
//
// Started on  Sun Dec 18 00:53:03 2016 kevin rochon
// Last update Mon Dec 19 17:17:13 2016 kevin rochon
//

#ifndef ACOMPONENT_HH_
# define ACOMPONENT_HH_

class	AComponent
{
public:
    enum Type
    {
        SPRITE,
        HITBOX
    };

protected:
  Type	_id;

 public:
  AComponent(const Type &id);
  virtual ~AComponent();
  virtual const Type	&getId() const;
  virtual void	setId(const Type &id);
};

#endif /* !ACOMPONENT_HH_ */
