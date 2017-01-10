#ifndef CORE_HPP_
# define CORE_HPP_

# include <SFML/Audio.hpp>
# include <SFML/Audio/Music.hpp>
# include "Graphique.hpp"
# include "Socket.hpp"

class Core
{
public:
	Core(const int &x = 1280, const int &y = 720, const std::string &title = "Such a great Rtype!");
	virtual ~Core();

	bool		isUp() const;
	bool		joinServer(const std::string &ip, const std::string &username);
	bool		run(const bool &);

private:
	Graphique	graphique;
	Socket		socket;
	sf::Music	music;
};

#endif /* !CORE_HPP_ */
