#ifndef SCENE_HPP_
# define SCENE_HPP_

# include <list>
# include "Object.hpp"
# include "Button.hpp"

class Scene
{
public:
	Scene();
	virtual ~Scene();
	bool							addObject(const Object &);
	bool							deleteObject(const Object &);
	bool							updateObject(const Object &);

	bool							loadFont(const std::string&);
	void							addText(const sf::Vector2f&, const std::string&, unsigned int = 30);
	const std::string				&getText(unsigned int id);
	void							addToText(unsigned int id, sf::Uint32);
	void							removeBackText(unsigned int id);
	void							addSprite(const sf::Vector2f&, const sf::Vector2f&, const std::string&, const sf::Vector2f&);
	void							setTextColor(unsigned int id, const sf::Color &clr);
	void							setButtonTextColor(unsigned int id, const sf::Color &clr);
	void							addButton(const sf::Vector2f&, const std::string&, const sf::Color& = sf::Color::Black, unsigned int = 30, bool = false);
	bool							buttonEvent(unsigned int id, const sf::Vector2f&);
	bool							buttonClik(unsigned int id, const sf::Vector2f&);
	void							draw(sf::RenderWindow &) const;
	const std::vector<sf::Text>		&getTextList() const;
	const std::vector<sf::Text>		&getTextButton() const;
	const std::vector<Button*>		&getButtons() const;
	const sf::Font					&getFont() const;
	const sf::Sprite				&getBGSprite() const;
	const sf::Texture				&getBGTexture() const;
	void							setBGSprite(const std::string &);
	void							setBGTexture(const std::string &);
	void							addButs(const std::string &, const sf::Vector2f &, const sf::Vector2f &, const sf::Color &, const sf::Color &, const Button::buttonEnum &);
	const Object					&getObj(std::string);
	void							setObjPos(std::string, int, int);

private:
	std::list<Object>				objects;

	sf::Font						font;
	std::string						wildString;

	std::vector<sf::Sprite>			sprites;
	std::vector<sf::Texture>		textures;
	std::vector<sf::RectangleShape>	rects;
	std::vector<sf::Text>			button_text;
	std::vector<sf::Text>			texts;
	std::vector<Button*>			buttons;
	sf::Sprite						BGSprite;
	sf::Texture						BGTexture;
};

#endif /* !SCENE_HPP_ */
