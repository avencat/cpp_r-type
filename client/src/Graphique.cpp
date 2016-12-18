#include "Graphique.hpp"

Graphique::Graphique(Socket &socket, const int &_x, const int &_y, const std::string &_title) : window(sf::VideoMode(_x, _y), _title), roomManager(socket)
{
	this->x = _x;
	this->y = _y;
	this->title = _title;
	this->open = true;
	this->ip = "";
	this->username = "";
	this->firstTime = true;
	this->activeScene = ScenesEnum::listRooms;
}

Graphique::~Graphique()
{
}

bool Graphique::initWindow(const int &_x, const int &_y, const std::string &_title)
{
	this->x = _x;
	this->y = _y;
	this->title = _title;
	return (true);
}

const std::string		&Graphique::getUsername() const
{
	return (username);
}

Scene	&Graphique::getActiveScene()
{
	switch (activeScene)
	{
	case ScenesEnum::getIp:
		return (linkServer);
	case ScenesEnum::loading:
		return (loading);
	case ScenesEnum::listRooms:
		return (listRooms);
	default:
		return (linkServer);
	}
}

bool Graphique::loadNextScene()
{
	firstTime = true;
	switch (activeScene)
	{
	case ScenesEnum::getIp:
		prevScene = activeScene;
		activeScene = ScenesEnum::loading;
		return (loadingScene());
	default:
		return (linkServerScene());
	}
}

bool Graphique::loadPrevScene()
{
	switch (prevScene)
	{
	case ScenesEnum::getIp:
		activeScene = prevScene;
		prevScene = ScenesEnum::null;
		return (linkServerScene());
	}
}

const std::string		&Graphique::getIp() const
{
	return (ip);
}

void					Graphique::setUsername(std::string str)
{
	this->username = str;
}

void					Graphique::setIp(std::string str)
{
	this->ip = str;
}

bool Graphique::refreshFrame()
{
	if (loadCurrentScene() == false)
		return (false);
	window.clear(sf::Color::Black);
	if (drawObject() == false)
		return (false);
	window.display();
	return (true);
}

bool Graphique::drawObject()
{
	getActiveScene().draw(window);
	return (true);
}

bool Graphique::closeWindow()
{
	this->open = false;
	this->window.close();
	return (true);
}

bool Graphique::isOpen() const
{
	return this->open;
}

bool Graphique::loadingScene()
{
	if (firstTime) {
		if (!loading.loadFont("./assets/fonts/Inconsolata-Regular.ttf"))
			return (false);

		// Title
		loading.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 50 * static_cast<float>(window.getSize().y) / 1080), "Loading...", 48);
		loading.setTextColor(0, sf::Color::White);
		firstTime = false;
	}
}

bool Graphique::loadCurrentScene()
{
	switch (activeScene)
	{
	case ScenesEnum::getIp:
		return (linkServerScene());
	case ScenesEnum::loading:
		return (loadingScene());
	case ScenesEnum::listRooms:
		return (showRoomScene());
	default:
		return (linkServerScene());
	}
}

bool Graphique::linkServerScene()
{
	if (firstTime) {
		focus = 0;

		if (!linkServer.loadFont("./assets/fonts/Inconsolata-Regular.ttf"))
			return (false);


		// IP
		linkServer.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 315 * static_cast<float>(window.getSize().y) / 1080), "Ip:");
		linkServer.addText(sf::Vector2f(90 * static_cast<float>(window.getSize().x) / 1920, 360 * static_cast<float>(window.getSize().y) / 1080), "");
		linkServer.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 360 * static_cast<float>(window.getSize().y) / 1080), ">");

		// Username
		linkServer.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 410 * static_cast<float>(window.getSize().y) / 1080), "Username:");
		linkServer.addText(sf::Vector2f(90 * static_cast<float>(window.getSize().x) / 1920, 455 * static_cast<float>(window.getSize().y) / 1080), "");
		linkServer.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 455 * static_cast<float>(window.getSize().y) / 1080), ">");

		// Button
		linkServer.addButton(sf::Vector2f(230 * static_cast<float>(window.getSize().x) / 1920, 550 * static_cast<float>(window.getSize().y) / 1080), "Connect");
		linkServer.addButton(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 360 * static_cast<float>(window.getSize().y) / 1080), "", sf::Color::Transparent, 30, true);
		linkServer.addButton(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 455 * static_cast<float>(window.getSize().y) / 1080), "", sf::Color::Transparent, 30, true);

		linkServer.setTextColor(2, sf::Color::Yellow);
		linkServer.setTextColor(5, sf::Color::Yellow);

		// Title
		linkServer.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 50 * static_cast<float>(window.getSize().y) / 1080), "R-Type", 48);
		linkServer.setTextColor(6, sf::Color::Red);
		firstTime = false;
	}

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			closeWindow();
			break;
		case sf::Event::MouseButtonPressed:
			pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			if (linkServer.buttonEvent(0, pos))
			{
				ip = linkServer.getText(1);
				username = linkServer.getText(4);
				loadNextScene();
				return (ip.length() > 0 && username.length() > 0);
			}
			else if (linkServer.buttonEvent(1, pos))
				focus = 0;
			else if (linkServer.buttonEvent(2, pos))
				focus = 1;
			break;
		case sf::Event::TextEntered:
			if (event.text.unicode < 128)
			{
				switch (event.text.unicode) {
				case 8:
					linkServer.removeBackText(focus == 0 ? 1 : 4);
					break;
				case 0:
					break;
				case 13:
					ip = linkServer.getText(1);
					username = linkServer.getText(4);
					loadNextScene();
					return (ip.length() > 0 && username.length() > 0);
					break;
				case 9:
					focus = focus ? 0 : 1;
					break;
				default:
					linkServer.addToText(focus == 0 ? 1 : 4, event.text.unicode);
					break;
				}
			}
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				closeWindow();
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
	linkServer.setTextColor(focus != 0 ? 4 : 1, sf::Color::Yellow);
	linkServer.setTextColor(focus != 0 ? 1 : 4, sf::Color::White);
	linkServer.setTextColor(focus != 0 ? 5 : 2, sf::Color::Yellow);
	linkServer.setTextColor(focus != 0 ? 2 : 5, sf::Color::White);
	return (true);
}

bool	Graphique::showRoomScene()
{
	int	j;

	j = 0;
	if (firstTime) {

		if (!listRooms.loadFont("./assets/fonts/Inconsolata-Regular.ttf"))
			return (false);

		listRooms.addText(sf::Vector2f(100 * static_cast<float>(window.getSize().x) / 1920, 100 * static_cast<float>(window.getSize().y) / 1080), "List of Room", 48);
		listRooms.setTextColor(0, sf::Color::Blue);

		//roomManager.roomList();
		for (std::list<Room>::const_iterator i = roomManager.getRooms().begin(); i != roomManager.getRooms().end(); i++) {
			listRooms.addButton(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, (j * 50 + 360) * static_cast<float>(window.getSize().y) / 1080), "Room", sf::Color::White, 30, true);
			j++;
		}
		for (std::list<Room>::const_iterator i = roomManager.getRooms().begin(); i != roomManager.getRooms().end(); i++) {
			listRooms.addButton(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, (j * 50 + 360) * static_cast<float>(window.getSize().y) / 1080), "Spectat' rooms", sf::Color::White, 30, true);
			j++;
		}
	}

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			closeWindow();
			break;
		case sf::Event::MouseButtonPressed:
			pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			for (int k = 0; k < roomManager.getRooms().size(); k++) {
				if (listRooms.buttonEvent(k, pos)) {
					if (k < roomManager.getRooms().size() / 2) {
						if (roomManager.joinRoom(k, false))
							return (true);
					}
					else {
						if (roomManager.joinRoom(k, true))
							return (true);
					}
					
				}
			}
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				closeWindow();
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
	return (true);
}