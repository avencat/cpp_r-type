#include "Object.hpp"

Object::Object()
{
	chargeShot = false;
}

Object::Object(const long &_longName, const sf::Vector2i &_pos, const sf::Vector2i &_dir, const int &_id)
{
	longName = _longName;
	pos = _pos;
	dir = _dir;
	id = _id;
	chargeShot = false;
	switch (_longName)
	{
	case 40:
		switch (_id)
		{
		case 0:
			addAComponent(_id, Sprite::TypeSpriteEnum::Player1, 0);
			break;
		case 1:
			addAComponent(_id, Sprite::TypeSpriteEnum::Player2, 0);
			break;
		case 2:
			addAComponent(_id, Sprite::TypeSpriteEnum::Player3, 0);
			break;
		case 3:
			addAComponent(_id, Sprite::TypeSpriteEnum::Player4, 0);
			break;
		default:
			break;
		}
		break;
	case 1:
		switch (_id)
		{
		case 2:
			addAComponent(_id, Sprite::TypeSpriteEnum::Load, 0);
			break;
		case 3:
			addAComponent(_id, Sprite::TypeSpriteEnum::Bullet, 0);
			break;
		default:
			break;
		}
		break;
	case 4:
		addAComponent(_id, Sprite::TypeSpriteEnum::RedShip, 0);
		break;
	case 5:
		addAComponent(_id, Sprite::TypeSpriteEnum::BrownSoldier, 0);
		break;
	default:
		break;
	} 
		
}

Object::~Object()
{
}

void		Object::setLoadVisible(const bool &visible)
{
	components.back().setVisible(visible);
}

const std::list<AComponent>		&Object::getComponents() const
{
	return (components);
}

void							Object::addAComponent(const int &_id, const Sprite::TypeSpriteEnum &_type, const int &lvl)
{
	AComponent		tmp;

	components.push_back(tmp);
	components.back().setId(_id);
	components.back().setSprite(_type, lvl);

}

void							Object::setRectCharge(const int &_id, const Sprite::TypeSpriteEnum &_type, const int &_lvl)
{
	for (std::list<AComponent>::iterator i = components.begin(); i != components.end(); i++) {
		if ((*i).getId() == _id) {
			(*i).setSprite(_type, _lvl);
		}
	}
}

const AComponent				&Object::getComponent(const int &_id) const
{
	for (std::list<AComponent>::const_iterator i = components.begin(); i != components.end(); i++) {
		if ((*i).getId() == _id) {
			return (*i);
		}
	}
	return (component);
}

const sf::Vector2i				&Object::getPos() const
{
	return (pos);
}

void							Object::setPos(const int &_x, const int &_y)
{
	pos.x = _x;
	pos.y = _y;
	for (std::list<AComponent>::iterator i = components.begin(); i != components.end(); i++) {
		if (i->getCSprite().getType() == Sprite::TypeSpriteEnum::Load)
			i->setPosition(_x + components.begin()->getCSprite().getSize().x, _y);
		else
			(*i).setPosition(_x, _y);
	}
}

void							Object::setLife(const int &_life)
{
	life = _life;
}

const int						&Object::getLife() const
{
	return (life);
}

void							Object::setScore(const int &_score)
{
	score = _score;
}

const int						&Object::getScore() const
{
	return (score);
}

const long						&Object::getLongName() const
{
	return (this->longName);
}

void							Object::setLongName(const long &name)
{
	this->longName = name;
}

const int						&Object::getId() const
{
	return (this->id);
}

void							Object::setId(const int &id)
{
	this->id = id;
}

const bool						&Object::getChargeShot() const
{
	return (chargeShot);
}

void							Object::setChargeShot(const bool &status)
{
	chargeShot = status;
}