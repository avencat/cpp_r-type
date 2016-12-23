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
	void					setSprite(const Sprite::TypeSpriteEnum &);
	const int				&getId() const;
	const Sprite			&getCSprite() const;

private:
	int						id;
	Sprite					sprite;
	Sprite::TypeSpriteEnum	type;
};

#endif /* !ACOMPONENT_HPP_ */
