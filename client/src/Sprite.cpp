#include "Sprite.hpp"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}

const sf::Sprite				&Sprite::getSprite() const
{
	return (sprite);
}

const Sprite::TypeSpriteEnum	&Sprite::getType() const
{
	return (type);
}

void							Sprite::setSprite(const Sprite::TypeSpriteEnum &_type, int lvl)
{
	texture.setSrgb(true);
	type = _type;
	switch (_type)
	{	
	case Sprite::TypeSpriteEnum::Player1:
		if (!texture.loadFromFile("./assets/Sprites/r-typesheet42.gif")) {
			std::cout << "Failed to load the texture Player 1" << std::endl;
		}
		setSpriteRect(lvl * 33, 0, 33, 17);
		break;
	case Sprite::TypeSpriteEnum::Player2:
		if (!texture.loadFromFile("./assets/Sprites/r-typesheet42.gif")) {
			std::cout << "Failed to load the texture Player 2" << std::endl;
		}
		setSpriteRect(lvl * 33, 17, 33, 17);
		break;
	case Sprite::TypeSpriteEnum::Player3:
		if (!texture.loadFromFile("./assets/Sprites/r-typesheet42.gif")) {
			std::cout << "Failed to load the texture Player 3" << std::endl;
		}
		setSpriteRect(lvl * 33, 34, 33, 17);
		break;
	case Sprite::TypeSpriteEnum::Player4:
		if (!texture.loadFromFile("./assets/Sprites/r-typesheet42.gif")) {
			std::cout << "Failed to load the texture Player 4" << std::endl;
		}
		setSpriteRect(lvl * 33, 51, 33, 17);
		break;
	case Sprite::TypeSpriteEnum::Bullet:
		if (!texture.loadFromFile("./assets/Sprites/r-typesheet1.gif")) {
			std::cout << "Failed to load the texture Bullet" << std::endl;
		}
		if (lvl == 1)
			setSpriteRect(186, 170, 78, 16);
		else if (lvl == 2)
			setSpriteRect(198, 152, 68, 16);
		else if (lvl == 3)
			setSpriteRect(216, 136, 48, 14);
		else if (lvl == 4)
			setSpriteRect(230, 120, 36, 12);
		break;
	case Sprite::TypeSpriteEnum::Load:
		if (!texture.loadFromFile("./assets/Sprites/r-typesheet1.gif")) {
			std::cout << "Failed to load the texture Load" << std::endl;
		}
		setSpriteRect(198, 54, 30, 26);
		break;
	case Sprite::TypeSpriteEnum::Ennemies:
		if (!texture.loadFromFile("./assets/Sprites/r-typesheet5.gif")) {
			std::cout << "Failed to load the texture ennemies" << std::endl;
		}
		setSpriteRect(lvl * 33, 0, 33, 36);
		break;
	default:
		break;
	}
	sprite.setTexture(texture);
}

void							Sprite::setSpriteRect(int _x1, int _y1, int _x2, int _y2)
{
	sprite.setTextureRect(sf::IntRect(_x1, _y1, _x2, _y2));
}

void							Sprite::setPosSprite(int _x, int _y)
{
	pos.first = _x;
	pos.second = _y;
	sprite.setPosition(sf::Vector2f(_x, _y));
}

const std::pair<int,int>		&Sprite::getPosSprite() const
{
	return (pos);
}