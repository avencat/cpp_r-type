#ifndef GRAPHIQUE_HPP_
# define GRAPHIQUE_HPP_

# include <string>
# include <list>
# include <SFML/Graphics.hpp>

class Graphique
{
public:
	Graphique(const int &_x, const int &_y, const std::string &_title);
	virtual ~Graphique();

	bool	initWindow(const int &_x, const int &_y, const std::string &_title);
	bool	refreshFrame();
	bool	drawObject();
	bool	closeWindow();

private:
	std::list<std::string>		rooms;
	sf::RenderWindow			window;
	int							x;
	int							y;
	std::string					title;
};

#endif /* !GRAPHIQUE_HPP_ */
