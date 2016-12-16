#ifndef GRAPHIQUE_HPP_
# define GRAPHIQUE_HPP_

# include <string>
# include <list>
# include <SFML/Graphics.hpp>

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

	const std::string		&getUsername(unsigned int id);
	const std::string		&getHost(unsigned int id);
	const int				&getPort(unsigned int id);
	void					setUsername(std::string);
	void					setHost(std::string);
	void					setPort(int);

private:
	std::list<std::string>		rooms;
	sf::RenderWindow			window;
	int							x;
	int							y;
	std::string					title;
	bool						open;

	std::string					ht;
	int							port;
	std::string					username;
};

#endif /* !GRAPHIQUE_HPP_ */
