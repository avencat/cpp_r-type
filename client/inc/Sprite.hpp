#ifndef SPRITE_HPP_
# define SPRITE_HPP_

# include <string>
# include <map>
# include <SFML/Graphics.hpp>
# include <iostream>

class Sprite
{
public:
	enum TypeSpriteEnum
	{
		Player1,
		Player2,
		Player3,
		Player4,
		Bullet,
		ennemies,
	};

	Sprite();
	~Sprite();
	
	void						setSprite(const TypeSpriteEnum &);
	void						setSpriteRect(int, int, int, int);
	const sf::Sprite			&getSprite() const;
	void						setPosSprite(int, int);
	const std::pair<int,int>	&getPosSprite() const;


private:
	std::pair<int, int>	pos;
	std::string			name;

	sf::Texture			texture;
	sf::Sprite			sprite;
	TypeSpriteEnum		type;
};

#endif /* !SPRITE_HPP_ */
