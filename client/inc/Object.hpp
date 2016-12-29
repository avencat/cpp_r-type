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
	void							addAComponent(int, const Sprite::TypeSpriteEnum &, int);
	const AComponent				&getComponent(int) const;
	const std::pair<int, int>		&getPos() const;
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
	
	std::string						name;
	long							longName;
	int								id;
	int								life;
	int								score;
	std::list<AComponent>			components;
	std::pair<int, int>				pos;

};

#endif /* !OBJECT_HPP_ */