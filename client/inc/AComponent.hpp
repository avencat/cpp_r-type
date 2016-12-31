#ifndef ACOMPONENT_HPP_
# define ACOMPONENT_HPP_

# include "Sprite.hpp"

class AComponent
{
public:
	AComponent();
	AComponent(int);
	virtual ~AComponent();

	void					setId(const int &);
	void					setPosition(int, int);
	void					setSprite(const Sprite::TypeSpriteEnum &, int);
	const int				&getId() const;
	const Sprite			&getCSprite() const;
	// getPos ne peut être marqué const car elle modifie pos avant de return.
	const sf::Vector2i		&getPos();
	const bool				&getVisible() const;
	void					setVisible(const bool &);

private:
	int						id;
	Sprite					sprite;
	Sprite::TypeSpriteEnum	type;
	sf::Vector2i			pos;
	bool				visible;
};

#endif /* !ACOMPONENT_HPP_ */
