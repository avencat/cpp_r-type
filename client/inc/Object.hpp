#ifndef OBJECT_HPP_
# define OBJECT_HPP_

# include <string>
# include <map>
# include <list>
# include <SFML/Graphics.hpp>
# include "AComponent.hpp"

class Object
{

public:
	Object();
	Object(const long &, const sf::Vector2i &, const sf::Vector2i &, const int &);
	virtual ~Object();

	const std::list<AComponent>		&getComponents() const;
	void							addAComponent(const int &, const Sprite::TypeSpriteEnum &, const int &);
	const AComponent				&getComponent(const int &) const;
	const sf::Vector2i				&getPos() const;
	void							setPos(const int &, const int &);
	void							setLife(const int &);
	const int						&getLife() const;
	void							setScore(const int &);
	const int						&getScore() const;
	const long						&getLongName() const;
	void							setLongName(const long &);
	const int						&getId() const;
	void							setId(const int &);

private:
	
	long							longName;
	int								id;
	int								life;
	int								score;
	std::list<AComponent>			components;
	sf::Vector2i					pos;
	sf::Vector2i					dir;
	AComponent						component;
};

#endif /* !OBJECT_HPP_ */