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
	virtual ~Object();

	const std::string				&getName() const;
	void							setName(const std::string &);
	const std::list<AComponent>		&getComponents() const;
	void							addAComponent(int, const Sprite::TypeSpriteEnum &);
	const AComponent				&getComponent(int) const;
	const std::pair<int, int>		&getPos() const;
	void							setPos(int, int);
	
private:
	
	std::string						name;
	std::list<AComponent>			components;
	std::pair<int, int>				pos;

};

#endif /* !OBJECT_HPP_ */