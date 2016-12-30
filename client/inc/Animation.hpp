#ifndef ANIMATION_HPP_
# define ANIMATION_HPP_

# include <list>
# include <SFML/System.hpp>
# include <SFML/System/Clock.hpp>

# include "Object.hpp"

class Animation
{
public:
	Animation();
	~Animation();

	void		refresh(sf::Clock, const std::list<Object> &);

private:

};

#endif /* !ANIMATION_HPP_ */