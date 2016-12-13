#include "..\inc\Graphique.hpp"

Graphique::Graphique(const int &_x, const int &_y, const std::string &_title) : window(sf::VideoMode(_x, _y), _title)
{
	this->x = _x;
	this->y = _y;
	this->title = _title;
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
	return (true);
}

bool Graphique::drawObject()
{
	return (true);
}

bool Graphique::closeWindow()
{
	return (true);
}
