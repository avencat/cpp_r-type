#ifndef SPRITE_HPP_
# define SPRITE_HPP_

# include <string>
# include <map>

class Sprite
{
public:
	Sprite();
	~Sprite();

private:
	std::pair<int, int>	pos;
	std::string			name;
};

#endif /* !SPRITE_HPP_ */
