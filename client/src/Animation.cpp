#include "Animation.hpp"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void		Animation::moveBackground(const sf::Clock &clock, Object &obj)
{
	sf::Time time = clock.getElapsedTime();
	obj.setPos(obj.getPos().x - static_cast<int>(time.asSeconds()), 0);

}

void		Animation::refresh(const sf::Clock &clock, std::list<Object> &objs)
{
	for (std::list<Object>::iterator i = objs.begin(); i != objs.end(); i++) {
		if ((*i).getLongName() == 100) {
			moveBackground(clock, (*i));
		}
	}
}