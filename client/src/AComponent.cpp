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

void					AComponent::setSprite(const Sprite::TypeSpriteEnum &_type, int lvl)
{
	sprite.setSprite(_type, lvl);
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

const sf::Vector2i		&AComponent::getPos()
{
	pos.x = sprite.getPosSprite().first;
	pos.y = sprite.getPosSprite().second;
	return (pos);
}
