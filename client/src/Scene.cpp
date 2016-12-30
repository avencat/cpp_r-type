#include "Scene.hpp"

#include <iostream>
#include <string>

Scene::Scene()
{
}

Scene::~Scene()
{
	for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); it = buttons.erase(it))
	{
		delete (*it);
	}
}

bool						Scene::addObject(const Object &obj)
{
	this->objects.push_back(obj);
	return (true);
}

bool						Scene::deleteObject(const Object &obj)
{
	for (std::list<Object>::iterator i = objects.begin(); i != objects.end(); i++)
	{
		if ((*i).getId() == obj.getId()) {
			this->objects.erase(i);
			return (true);
		}
	}
	return (false);
}

bool						Scene::updateObject(const Object &obj)
{
	for (std::list<Object>::iterator i = objects.begin(); i != objects.end(); i++)
	{
		if ((*i).getId() == obj.getId()) {
			(*i) = obj;
			return (true);
		}
	}
	return (false);
}

bool						Scene::loadFont(const std::string &fontName)
{
	if (!font.loadFromFile(fontName)) {
		return (false);
	}
	for (std::vector<sf::Text>::iterator i = texts.begin(); i != texts.end(); i++)
	{
		(*i).setFont(font);
	}
	return (true);
}

const std::string			&Scene::getText(const unsigned int &id)
{
	wildString = "";
	if (id > texts.size())
		return (wildString);
	wildString = texts[id].getString();
	return (wildString);
}

const std::vector<sf::Text>	&Scene::getTextList() const
{
	return (texts);
}

const sf::Font					&Scene::getFont() const
{
	return (font);
}

void						Scene::addToText(const unsigned int &id, const sf::Uint32 &c)
{
	std::string tmp;

	if (id< texts.size())
	{
		tmp = texts[id].getString();
		tmp += static_cast<char>(c);
		texts[id].setString(tmp);
	}
}

void						Scene::removeBackText(const unsigned int &id)
{
	std::string tmp;

	if (id < texts.size())
	{
		tmp = texts[id].getString();
		if (tmp.size() > 0)
			tmp.pop_back();
		texts[id].setString(tmp);
	}
}

void						Scene::addSprite(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &file, const sf::Vector2f &winsize)
{
	sf::Texture tx;
	sf::IntRect ir;

	if (!tx.loadFromFile(file))
		return;
	textures.push_back(tx);
	ir.left = pos.x;
	ir.top = pos.y;
	ir.width = size.x;
	ir.height = size.y;
	sprites.push_back(sf::Sprite(textures.back(), ir));
	sprites.back().setScale(winsize.x / 1920, winsize.y / 1080);
}

void						Scene::setTextColor(const unsigned int &id, const sf::Color &color)
{
	if (id <= texts.size())
		texts[id].setColor(color);
}

void						Scene::setButtonTextColor(const unsigned int &id, const sf::Color &color)
{
	if (id <= button_text.size())
		button_text[id].setColor(color);
}

void						Scene::addText(const sf::Vector2f &pos, const std::string &str, const unsigned int &size)
{
	texts.push_back(sf::Text(str, font, size));
	texts.back().setPosition(pos);
}

const std::vector<sf::Text>	&Scene::getTextButton() const
{
	return (button_text);
}

void						Scene::addButton(const sf::Vector2f &pos, const std::string &str, const sf::Color &clr, const unsigned int &size, const bool &full)
{
	rects.push_back(sf::RectangleShape());
	rects.back().setPosition(pos);
	rects.back().setSize(sf::Vector2f(static_cast<float>(full ? 1920 : str.length() + 20) * 5, static_cast<float>(size + 15)));
	rects.back().setFillColor(clr);
	button_text.push_back(sf::Text(str, font, size));
	button_text.back().setPosition(pos.x + 25, pos.y + 5);
	button_text.back().setCharacterSize(size);
}

bool						Scene::buttonEvent(const unsigned int &id, const sf::Vector2f &pos)
{
	sf::FloatRect fr;

	if (id < rects.size())
	{
		fr = rects[id].getGlobalBounds();
		if (pos.x <= fr.left + fr.width && pos.x >= fr.left && pos.y <= fr.top + fr.height && pos.y >= fr.top)
			return (true);
	}
	return (false);
}

bool						Scene::buttonClik(const unsigned int &id, const sf::Vector2f &pos)
{
	sf::FloatRect fr;

	if (id < buttons.size())
	{
		fr = buttons[id]->getRect().getGlobalBounds();
		if (pos.x <= fr.left + fr.width && pos.x >= fr.left && pos.y <= fr.top + fr.height && pos.y >= fr.top)
			return (true);
	}
	return (false);
}

const std::vector<Button*>	&Scene::getButtons() const
{
	return (buttons);
}

const Object				&Scene::getObj(long _name)
{
	for (std::list<Object>::const_iterator it = objects.begin(); it != objects.end(); it++) {
		if ((*it).getLongName() == _name)
			return ((*it));
	}
	return (objects.back());
}
//
//Object				&Scene::getObj(const long &_name)
//{
//	for (std::list<Object>::iterator it = objects.begin(); it != objects.end(); it++) {
//		if ((*it).getLongName() == _name)
//			return ((*it));
//	}
//	return (objects.back());
//}

void						Scene::setObjPos(const int &_id, const sf::Vector2i &_pos)
{
	for (std::list<Object>::iterator it = objects.begin(); it != objects.end(); it++) {
		if ((*it).getId() == _id)
			(*it).setPos(_pos.x, _pos.y);
	}
}

void						Scene::setSEndGame(const bool &status)
{
	endGame = status;
}

const bool					&Scene::getEndGame() const
{
	return (endGame);
}

const sf::Clock				&Scene::getClock() const
{
	return (clock);
}

void						Scene::addButs(const std::string &_name, const sf::Vector2f &_pos, const sf::Vector2f &_size, const sf::Color &_clrTxt, const sf::Color &_clrBg, const Button::buttonEnum &butEnum)
{
	buttons.push_back(new Button(font, _name, _pos, _size, _clrTxt, _clrBg, butEnum));
}

bool						Scene::destroyById(const int &_id)
{
	for (std::list<Object>::iterator i = objects.begin(); i != objects.end(); i++) {
		if ((*i).getId() == _id) {
			this->objects.erase(i);
			return (true);
		}
	}
	return (false);
}

void							Scene::refreshAnimation()
{
	animation.refresh(clock, objects);
}

void							Scene::restartClock()
{
	clock.restart();
}

void						Scene::draw(sf::RenderWindow &window) const
{
	for (std::vector<sf::Sprite>::const_iterator it = sprites.begin(); it != sprites.end(); it++) {
		window.draw(*it);
	}
	for (std::vector<sf::RectangleShape>::const_iterator it = rects.begin(); it != rects.end(); it++) {
		window.draw(*it);
	}
	for (std::vector<sf::Text>::const_iterator it = texts.begin(); it != texts.end(); it++) {
		window.draw(*it);
	}
	for (std::vector<sf::Text>::const_iterator it = button_text.begin(); it != button_text.end(); it++) {
		window.draw(*it);
	}
	for (std::vector<Button*>::const_iterator it = buttons.begin(); it != buttons.end(); it++) {
		window.draw((*it)->getRect());
		window.draw((*it)->getText());
	}
	for (std::list<Object>::const_iterator it = objects.begin(); it != objects.end(); it++) {
		for (std::list<AComponent>::const_iterator i = it->getComponents().begin(); i != it->getComponents().end(); i++) {
			window.draw((*i).getCSprite().getSprite());
		}
	}
}
