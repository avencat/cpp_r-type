#ifndef SPRITE_HPP_
# define SPRITE_HPP_

# ifdef _WIN32
#  include <SFML/Graphics.hpp>
# else
#  include <SFML2.2/Graphics.hpp>
# endif

# include <string>
# include <map>
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
		Load,
		Ennemies,
		Background,
	};

	Sprite();
	~Sprite();

	void						setSprite(const TypeSpriteEnum &,int);
	void						setSpriteRect(int, int, int, int);
	const sf::Sprite			&getSprite() const;
	const TypeSpriteEnum		&getType() const;
	void						setPosSprite(int, int);
	const std::pair<int,int>	&getPosSprite() const;


private:
	std::pair<int, int>	pos;
	std::string			name;
	int					level;

	sf::Texture			texture;
	sf::Sprite			sprite;
	TypeSpriteEnum		type;
};

#endif /* !SPRITE_HPP_ */
