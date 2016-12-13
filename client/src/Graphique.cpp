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
	if (drawObject() == false)
		return (false);
	window.display();
	return (true);
}

bool Graphique::drawObject()
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	window.draw(shape);
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
