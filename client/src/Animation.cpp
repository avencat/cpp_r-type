#include "Animation.hpp"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void		Animation::moveBackground(Object &obj, const sf::Time &time)
{
	if (obj.getPos().x >= -(static_cast<int>(obj.getComponent(1).getCSprite().getSize().x))) {
		obj.setPos(obj.getPos().x - static_cast<int>(time.asSeconds()) - 1, 0);
	}
	else {
		obj.setPos(static_cast<int>(obj.getComponent(1).getCSprite().getSize().x) * 2 + (obj.getPos().x + static_cast<int>(obj.getComponent(1).getCSprite().getSize().x)) - static_cast<int>(time.asSeconds()) - 1, 0);
	}
}

void		Animation::refresh(const sf::Clock &clock, std::list<Object> &objs)
{
	sf::Time time = clock.getElapsedTime();
	for (std::list<Object>::iterator i = objs.begin(); i != objs.end(); i++) {
		if ((*i).getLongName() >= 100 && (*i).getLongName() <= 102) {
			moveBackground((*i), time);
		}
	}
}
