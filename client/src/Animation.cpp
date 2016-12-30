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
	if (obj.getPos().x >= (0 - static_cast<int>(obj.getComponent(1).getCSprite().getTexture().getSize().x))) {
		obj.setPos(obj.getPos().x - static_cast<int>(time.asSeconds()) - 1, 0);
	}
	else
		obj.setPos(static_cast<int>(obj.getComponent(1).getCSprite().getTexture().getSize().x), 0);
}

void		Animation::refresh(const sf::Clock &clock, std::list<Object> &objs)
{
	for (std::list<Object>::iterator i = objs.begin(); i != objs.end(); i++) {
		if ((*i).getLongName() == 100 || (*i).getLongName() == 101) {
			moveBackground(clock, (*i));
		}
	}
}