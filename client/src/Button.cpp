#include "Button.hpp"

Button::Button()
{
}

Button::Button(const sf::Font &_font, const std::string &name, const sf::Vector2f &pos, const sf::Vector2f &size, const sf::Color &clrTxt, const sf::Color &clrBg, const buttonEnum &_id)
{
	id = _id;
	rFont = _font;
	text = sf::Text(name, rFont);
	text.setPosition(pos);
	if (_id != buttonEnum::Room) {
		sf::Vector2f newPos = pos;
		newPos.x = newPos.x + ((size.x - text.getLocalBounds().width) / 2);
		newPos.y = newPos.y + ((size.y - text.getLocalBounds().height) / 4);
		text.setPosition(newPos);
	}
	text.setColor(clrTxt);
	colorTxt = clrTxt;
	rect.setPosition(pos);
	rect.setSize(size);
	rect.setFillColor(clrBg);
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(2);
	colorBg = clrBg;
}

Button::~Button()
{
}

Button::Button(const Button &button)
{
	text = button.text;
	rect = button.rect;
	colorTxt = button.colorTxt;
	colorBg = button.colorBg;
	rFont = button.rFont;
}

Button						&Button::operator=(const Button &button)
{
	this->text = button.text;
	this->rect = button.rect;
	this->colorTxt = button.colorTxt;
	this->colorBg = button.colorBg;
	this->rFont = button.rFont;
	this->id = button.id;
	return (*this);
}

bool						Button::setFont(const std::string &str)
{
	if (!rFont.loadFromFile(str))
		return (false);
	text.setFont(rFont);
	return (true);
}

void						Button::setText(const std::string &str)
{
	text.setString(str);
}

void						Button::setRect(const sf::Vector2f &pos, const sf::Vector2f &size)
{
	rect.setPosition(pos);
	rect.setSize(size);
}

void						Button::setTxtColor(const sf::Color &clr)
{
	text.setColor(clr);
	colorTxt = clr;
}

void						Button::setBgColor(const sf::Color &clr)
{
	rect.setFillColor(clr);
	colorBg = clr;
}

const Button::buttonEnum			&Button::getId() const
{
	return (id);
}

const sf::Text				&Button::getText() const
{
	return (text);
}

const sf::RectangleShape	&Button::getRect() const
{
	return (rect);
}

const sf::Color				&Button::getColorTxt() const
{
	return (colorTxt);
}

const sf::Color				&Button::getColorBg() const
{
	return (colorBg);
}