#ifndef GRAPHIQUE_HPP_
# define GRAPHIQUE_HPP_

# include <string>
# include <list>
# include <SFML/Graphics.hpp>
# include <iostream>

# include "Scene.hpp"

enum ScenesEnum
{
	getIp,
	loading,
	null,
};

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
	bool	loadingScene();
	bool	loadCurrentScene();

	const std::string		&getUsername() const;
	const std::string		&getIp() const;
	void					setUsername(std::string);
	void					setIp(std::string);
	Scene					&getActiveScene();
	bool					loadNextScene();
	bool					loadPrevScene();

private:
	std::list<std::string>		rooms;
	sf::RenderWindow			window;
	int							x;
	int							y;
	std::string					title;
	bool						open;
	bool						firstTime;

	std::string					ip;
	std::string					username;
	Scene						linkServer;
	Scene						loading;
	Scene						listRooms;
	sf::Event					event;
	sf::Vector2f				pos;
	char						focus;
	ScenesEnum					activeScene;
	ScenesEnum					prevScene;
};

#endif /* !GRAPHIQUE_HPP_ */
