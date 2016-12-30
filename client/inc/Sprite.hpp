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

	void						setSprite(const TypeSpriteEnum &, const int &);
	void						setSpriteRect(const int &, const int &, const int &, const int &);
	void                        setPosSprite(const int &, const int &);
	const sf::Sprite			&getSprite() const;
	const TypeSpriteEnum		&getType() const;
	const sf::Texture			&getTexture() const;
	const std::pair<int,int>	&getPosSprite() const;
	const sf::Vector2f		&getSize() const;


private:
	std::pair<int, int>	pos;
	std::string			name;
	int					level;

	sf::Texture			texture;
	sf::Sprite			sprite;
	TypeSpriteEnum		type;
	sf::Vector2f		size;
};

#endif /* !SPRITE_HPP_ */
