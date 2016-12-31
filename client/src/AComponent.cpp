#include "AComponent.hpp"

AComponent::AComponent()
{
	visible = true;
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
	if (_type == Sprite::TypeSpriteEnum::Null) {
		sprite.setSpriteRect(lvl * 30, 54, 30, 26);
	}
	else {
		sprite.setSprite(_type, lvl);
	}
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
	if (type == Sprite::Load)
		sprite.setPosSprite(x + 20, y);
	else
		sprite.setPosSprite(x, y);
}

const sf::Vector2i		&AComponent::getPos()
{
	pos.x = sprite.getPosSprite().first;
	pos.y = sprite.getPosSprite().second;
	return (pos);
}

const bool & AComponent::getVisible() const
{
	return (visible);
}

void AComponent::setVisible(const bool &_visible)
{
	visible = _visible;
}
