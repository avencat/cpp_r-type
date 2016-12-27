#include "AComponent.hpp"

AComponent::AComponent()
{
}

AComponent::AComponent(int _id)
{
	id = _id;
}

AComponent::~AComponent()
{
}

void					AComponent::setId(const int &_id)
{
	id = _id;
}

void					AComponent::setSprite(const Sprite::TypeSpriteEnum &type, int lvl)
{
	sprite.setSprite(type, lvl);
}

const int				&AComponent::getId() const
{
	return (id);
}

const Sprite			&AComponent::getCSprite() const
{
	return (sprite);
}

void					AComponent::setPosition(int x, int y)
{
	sprite.setPosSprite(x, y);
}

const sf::Vector2i		&AComponent::getPos() const
{
	sf::Vector2i		tmp;

	tmp.x = sprite.getPosSprite().first;
	tmp.y = sprite.getPosSprite().second;
	return (tmp);
}