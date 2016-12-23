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

void					AComponent::setSprite(const Sprite::TypeSpriteEnum &type)
{
	sprite.setSprite(type);
}

const int				&AComponent::getId() const
{
	return (id);
}

const Sprite			&AComponent::getCSprite() const
{
	return (sprite);
}