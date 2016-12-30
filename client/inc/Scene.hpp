#ifndef SCENE_HPP_
# define SCENE_HPP_

# ifdef _WIN32
#  include <SFML/System.hpp>
#  include <SFML/System/Clock.hpp>
# else
#  include <SFML2.2/System.hpp>
#  include <SFML2.2/System/Clock.hpp>
# endif

# include <list>
# include "Object.hpp"
# include "Button.hpp"
# include "Animation.hpp"

class Scene
{
public:
	Scene();
	virtual ~Scene();
	bool							addObject(const Object &);
	bool							deleteObject(const Object &);
	bool							updateObject(const Object &);

	bool							loadFont(const std::string&);
	void							addText(const sf::Vector2f&, const std::string&, const unsigned int & = 30);
	const std::string				&getText(const unsigned int &id);
	void							addToText(const unsigned int &id, const sf::Uint32 &);
	void							removeBackText(const unsigned int &id);
	void							addSprite(const sf::Vector2f&, const sf::Vector2f&, const std::string&, const sf::Vector2f&);
	void							setTextColor(const unsigned int &id, const sf::Color &clr);
	void							setButtonTextColor(const unsigned int &id, const sf::Color &clr);
	void							addButton(const sf::Vector2f&, const std::string&, const sf::Color& = sf::Color::Black, const unsigned int & = 30, const bool & = false);
	bool							buttonEvent(const unsigned int &id, const sf::Vector2f&);
	bool							buttonClik(const unsigned int &id, const sf::Vector2f&);
	void							draw(sf::RenderWindow &) const;
	const std::vector<sf::Text>		&getTextList() const;
	const std::vector<sf::Text>		&getTextButton() const;
	const std::vector<Button*>		&getButtons() const;
	const sf::Font					&getFont() const;
	const sf::Clock					&getClock() const;
	void							refreshAnimation();


	void							addButs(const std::string &, const sf::Vector2f &, const sf::Vector2f &, const sf::Color &, const sf::Color &, const Button::buttonEnum &);
	//Object							&getObj(const long &);
	const Object					&getObj(long);
	void							setObjPos(const int &, const sf::Vector2i &);
	void							setSEndGame(const bool &);
	const bool						&getEndGame() const;
	bool							destroyById(const int &);

private:
	std::list<Object>				objects;
	bool							endGame;

	sf::Font						font;
	std::string						wildString;

	std::vector<sf::Sprite>			sprites;
	std::vector<sf::Texture>		textures;
	std::vector<sf::RectangleShape>	rects;
	std::vector<sf::Text>			button_text;
	std::vector<sf::Text>			texts;
	std::vector<Button*>			buttons;
	Animation						animation;
	sf::Clock						clock;

};

#endif /* !SCENE_HPP_ */
