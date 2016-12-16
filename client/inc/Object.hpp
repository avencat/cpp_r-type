#ifndef OBJECT_HPP_
# define OBJECT_HPP_

# include <string>
# include <map>
# include <list>
# include "AComponent.hpp"
# include <SFML/Graphics.hpp>

class Object
{
public:
	Object();
	virtual ~Object();

	const std::string		&getName() const;
	void					setName(const std::string &);
	
private:
	
	std::string						name;
	std::list<AComponent>			components;
	std::pair<int, int>				pos;

	
};

#endif /* !OBJECT_HPP_ */
