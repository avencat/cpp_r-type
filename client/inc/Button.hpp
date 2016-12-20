#pragma once
# ifndef BUTTON_H_
# define BUTTON_H_

# include <SFML/Graphics.hpp>
# include <string>

class Button
{
public:

	enum buttonEnum
	{
		Player,
		Spectat,
		Create,
		Room,
		Ready,
		NotReady,
		Leave,
	};

	Button();
	Button(const sf::Font &, const std::string &, const sf::Vector2f &, const sf::Vector2f &, const sf::Color &, const sf::Color &, const buttonEnum &);
	~Button();
	Button(const Button &);
	Button						&operator=(const Button &);

	void						setText(const std::string &);
	void						setRect(const sf::Vector2f &, const sf::Vector2f &);
	void						setTxtColor(const sf::Color &);
	void						setBgColor(const sf::Color &);
	bool						setFont(const std::string &);
	const sf::Text				&getText() const;
	const sf::RectangleShape	&getRect() const;
	const sf::Color				&getColorTxt() const;
	const sf::Color				&getColorBg() const;
	const buttonEnum			&getId() const;

private:
	sf::Text			text;
	sf::RectangleShape	rect;
	sf::Color			colorTxt;
	sf::Color			colorBg;
	sf::Font			rFont;
	buttonEnum			id;
};

#endif /* !BUTTON_H_*/