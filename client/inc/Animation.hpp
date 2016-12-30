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

	void		refresh(const sf::Clock &, std::list<Object> &);
	void		moveBackground(const sf::Clock &, Object &);

private:

};

#endif /* !ANIMATION_HPP_ */