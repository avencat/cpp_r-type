#include "..\inc\Graphique.hpp"

Graphique::Graphique(const int &_x, const int &_y, const std::string &_title) : window(sf::VideoMode(_x, _y), _title)
{
	this->x = _x;
	this->y = _y;
	this->title = _title;
	this->open = true;
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

const std::string		&Graphique::getUsername(unsigned int id)
{
	return (username);
}

const std::string		&Graphique::getHost(unsigned int id)
{
	return (ht);
}

const int				&Graphique::getPort(unsigned int id)
{
	return (port);
}

void					Graphique::setUsername(std::string str)
{
	this->username = str;
}

void					Graphique::setHost(std::string str)
{
	this->ht = str;
}

void					Graphique::setPort(int host)
{
	this->ht = host;
}

bool Graphique::refreshFrame()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			this->closeWindow();
			return (true);
		}
	}
	window.clear();
	if (linkServerScene() == false)
		return (false);
	if (drawObject() == false)
		return (false);
	window.display();
	return (true);
}

bool Graphique::drawObject()
{
	linkServerScene();
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

bool Graphique::linkServerScene()
{
	Scene			linkServer;
	sf::Event		event;
	sf::Vector2f	pos;
	char			focus;
	std::string		host;

	focus = 0;

	if (!linkServer.loadFont("./assets/fonts/Inconsolata-Regular.ttf"))
		return (false);

	
	// Host / IP
	linkServer.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 315 * static_cast<float>(window.getSize().y) / 1080), "Hostname:");
	linkServer.addText(sf::Vector2f(90 * static_cast<float>(window.getSize().x) / 1920, 360 * static_cast<float>(window.getSize().y) / 1080), "");
	linkServer.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 360 * static_cast<float>(window.getSize().y) / 1080), ">");
	
	// Port
	linkServer.addText(sf::Vector2f(50 * static_cast<float>(window.getSize().x) / 1920, 410 * static_cast<float>(window.getSize().y) / 1080), "Port:");
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
	linkServer.setTextColor(1, sf::Color::Red);


	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.clear();
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
				if (linkServer.buttonEvent(0, pos))
				{
					host = linkServer.getText(1);
					port = atoi(linkServer.getText(3).c_str());
					return (atoi(linkServer.getText(3).c_str()));
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
						host = linkServer.getText(1);
						return (atoi(linkServer.getText(3).c_str()));
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
					window.clear();
					window.close();
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
		linkServer.setTextColor(focus ? 3 : 1, sf::Color::Yellow);
		linkServer.setTextColor(focus ? 1 : 3, sf::Color::White);
		linkServer.setTextColor(focus ? 5 : 4, sf::Color::Yellow);
		linkServer.setTextColor(focus ? 4 : 5, sf::Color::White);
		window.clear(sf::Color::Black);
		linkServer.draw(window);
		window.display();
	}
	return (true);
}