#include "Sprite.hpp"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

const sf::Sprite			&Sprite::getSprite() const
{
	return (sprite);
}

void						Sprite::setSprite(const Sprite::TypeSpriteEnum &_type)
{
	type = _type;
	switch (_type)
	{	
	case Sprite::TypeSpriteEnum::Player1:
		if (!texture.loadFromFile("/assets/Sprites/r-typesheet42.gif")) {
			std::cout << "Failed to load the texture Player 1" << std::endl;
		}
		break;
	case Sprite::TypeSpriteEnum::Player2:
		if (!texture.loadFromFile("/assets/Sprites/r-typesheet42.gif")) {
			std::cout << "Failed to load the texture Player 2" << std::endl;
		}
		break;
	case Sprite::TypeSpriteEnum::Player3:
		if (!texture.loadFromFile("/assets/Sprites/r-typesheet42.gif")) {
			std::cout << "Failed to load the texture Player 3" << std::endl;
		}
		break;
	case Sprite::TypeSpriteEnum::Player4:
		if (!texture.loadFromFile("/assets/Sprites/r-typesheet42.gif")) {
			std::cout << "Failed to load the texture Player 4" << std::endl;
		}
		break;
	case Sprite::TypeSpriteEnum::Bullet:
		if (!texture.loadFromFile("/assets/Sprites/r-typesheet43.gif")) {
			std::cout << "Failed to load the texture Bullet" << std::endl;
		}
		break;
	case Sprite::TypeSpriteEnum::ennemies:
		if (!texture.loadFromFile("/assets/Sprites/r-typesheet2.gif")) {
			std::cout << "Failed to load the texture ennemies" << std::endl;
		}
		break;
	default:
		break;
	}
	
	sprite.setTexture(texture);
}

void						Sprite::setSpriteRect(int _x1, int _y1, int _x2, int _y2)
{
	sprite.setTextureRect(sf::IntRect(_x1, _y1, _x2, _y2));
}

void						Sprite::setPosSprite(int _x, int _y)
{
	pos.first = _x;
	pos.second = _y;
}

const std::pair<int,int>	&Sprite::getPosSprite() const
{
	return (pos);
}