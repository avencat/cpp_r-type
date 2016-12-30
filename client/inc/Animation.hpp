#ifndef ANIMATION_HPP_
# define ANIMATION_HPP_

# ifdef _WIN32
#  include <SFML/System.hpp>
#  include <SFML/System/Clock.hpp>
# else
#  include <SFML2.2/System.hpp>
#  include <SFML2.2/System/Clock.hpp>
# endif

# include <list>
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
