#ifndef CORE_HPP_
# define CORE_HPP_

# include "Graphique.hpp"
# include "Socket.hpp"

class Core
{
public:
	Core(const int &x = 1280, const int &y = 720, const std::string &title = "Such a great Rtype!");
	virtual ~Core();

	bool		isUp() const;
	bool		joinServer(const std::string &ip, const std::string &username);
	bool		run();

private:
	Graphique	graphique;
	Socket		socket;
};

#endif /* !CORE_HPP_ */
