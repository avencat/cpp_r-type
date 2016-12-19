#include "Scene.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
}

bool Scene::addObject(const Object &obj)
{
	this->objects.push_back(obj);
	return (true);
}

bool Scene::deleteObject(const Object &obj)
{
	for (std::list<Object>::const_iterator i = objects.begin(); i != objects.end(); i++)
	{
		if ((*i).getName() == obj.getName()) {
			this->objects.erase(i);
			return (true);
		}
	}
	return (false);
}

bool Scene::updateObject(const Object &obj)
{
	return (false);
}

bool Scene::loadFont(const std::string &fontName)
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

const std::string &Scene::getText(unsigned int id)
{
	wildString = "";
	if (id > texts.size())
		return (wildString);
	wildString = texts[id].getString();
	return (wildString);
}

void Scene::addToText(unsigned int id, sf::Uint32 c)
{
	std::string tmp;

	if (id< texts.size())
	{
		tmp = texts[id].getString();
		tmp += static_cast<char>(c);
		texts[id].setString(tmp);
	}
}

void Scene::removeBackText(unsigned int id)
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

void Scene::addSprite(const sf::Vector2f &pos, const sf::Vector2f &size, const std::string &file, const sf::Vector2f &winsize)
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

void Scene::setTextColor(unsigned int id, const sf::Color &color)
{
	if (id <= texts.size())
		texts[id].setColor(color);
}

void Scene::setButtonTextColor(unsigned int id, const sf::Color &color)
{
	if (id <= button_text.size())
		button_text[id].setColor(color);
}

void Scene::addText(const sf::Vector2f &pos, const std::string &str, unsigned int size)
{
	texts.push_back(sf::Text(str, font, size));
	texts.back().setPosition(pos);
}

void Scene::addButton(const sf::Vector2f &pos, const std::string &str, const sf::Color &clr, unsigned int size, bool full)
{
	rects.push_back(sf::RectangleShape());
	rects.back().setPosition(pos);
	rects.back().setSize(sf::Vector2f(static_cast<float>(full ? 1920 : str.length() + 20) * 5, static_cast<float>(size + 15)));
	rects.back().setFillColor(clr);
	button_text.push_back(sf::Text(str, font, size));
	button_text.back().setPosition(pos.x + 25, pos.y + 5);
	button_text.back().setCharacterSize(size);
}

bool Scene::buttonEvent(unsigned int id, const sf::Vector2f &pos)
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

void Scene::draw(sf::RenderWindow &window)
{
	for (std::vector<sf::Sprite>::iterator it = sprites.begin(); it != sprites.end(); it++)
	{
		window.draw(*it);
	}
	for (std::vector<sf::RectangleShape>::iterator it = rects.begin(); it != rects.end(); it++)
	{
		window.draw(*it);
	}
	for (std::vector<sf::Text>::iterator it = texts.begin(); it != texts.end(); it++)
	{
		window.draw(*it);
	}
	for (std::vector<sf::Text>::iterator it = button_text.begin(); it != button_text.end(); it++)
	{
		window.draw(*it);
	}
}