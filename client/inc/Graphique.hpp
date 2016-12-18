#ifndef GRAPHIQUE_HPP_
# define GRAPHIQUE_HPP_

# include <string>
# include <list>
# include <SFML/Graphics.hpp>
# include <iostream>

# include "Scene.hpp"

class Graphique
{
public:
	Graphique(const int &_x, const int &_y, const std::string &_title);
	virtual ~Graphique();

	bool	initWindow(const int &_x, const int &_y, const std::string &_title);
	bool	refreshFrame();
	bool	drawObject();
	bool	closeWindow();
	bool	isOpen() const;
	bool	linkServerScene();

	const std::string		&getUsername() const;
	const std::string		&getIp() const;
	void					setUsername(std::string);
	void					setIp(std::string);

private:
	std::list<std::string>		rooms;
	sf::RenderWindow			window;
	int							x;
	int							y;
	std::string					title;
	bool						open;

	std::string					ip;
	std::string					username;
};

#endif /* !GRAPHIQUE_HPP_ */
