#ifndef GRAPHIQUE_HPP_
# define GRAPHIQUE_HPP_

# ifdef _WIN32
#  include <SFML/Graphics.hpp>
# else
#  include <SFML2.2/Graphics.hpp>
# endif

# include <string>
# include <list>
# include <iostream>
# include "Scene.hpp"
# include "RoomManager.hpp"
# include "PlayerLink.hpp"

enum ScenesEnum
{
	getIp,
	loading,
	listRooms,
	lobby,
	InGame,
	null,
};

enum StatusEnum
{
	Player,
	Spectator,
};

class Graphique
{
public:
	Graphique(Socket &socket, const int &_x, const int &_y, const std::string &_title);
	virtual ~Graphique();

	bool						initWindow(const int &_x, const int &_y, const std::string &_title);
	bool						refreshFrame();
	bool						drawObject();
	bool						closeWindow();
	bool						isOpen() const;
	bool						linkServerScene();
	bool						loadingScene();
	bool						loadCurrentScene();
	bool						showRoomScene();
	bool						lobbyScene();
	bool						inGameScene();

	const std::string			&getUsername() const;
	const std::string			&getIp() const;
	const StatusEnum			&getStatusUser() const;
	void						setStatusUser(const StatusEnum &);
	void						setUsername(const std::string &);
	void						setIp(const std::string &);
	Scene						&getActiveScene();
	bool						loadNextScene();
	bool						loadPrevScene();
	bool						handleServerCode();
	bool						loadScene(const ScenesEnum);

private:
	std::list<std::string>		rooms;
	sf::RenderWindow			window;
	int							x;
	int							y;
	std::string					title;
	bool						open;
	bool						firstTime;
	RoomManager					roomManager;

	std::string					ip;
	std::string					username;
	Scene						linkServer;
	Scene						loading;
	Scene						listRooms;
	Scene						lobby;
	Scene						inGame;
	sf::Event					event;
	sf::Vector2f				pos;
	char						focus;
	ScenesEnum					activeScene;
	ScenesEnum					prevScene;
	StatusEnum					user;
	Socket						&socket;

	// Scene In Game
	unsigned short				isCharging;
	Object						mainShip;
	sf::Vector2f				position;
	sf::Vector2f				velocity;
	float						maxspeed;
	float						accel;
	float						decel;
	float						actualspeed;
	char							life;
	Object						newObject;
	long							score;
	PlayerLink				link;
	short						newX;
	short						newY;
	short						oldX;
	short						oldY;
	short						mainShipId;
};

#endif /* !GRAPHIQUE_HPP_ */
