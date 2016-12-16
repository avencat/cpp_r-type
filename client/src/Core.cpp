#include "Core.hpp"

Core::Core(const int &_x, const int &_y, const std::string &_title) : graphique(_x, _y, _title)
{
	graphique.initWindow(_x, _y, _title);
}

Core::~Core()
{
}

bool Core::isUp() const
{
	return (this->graphique.isOpen());
}

bool Core::joinServer(const std::string &ip, const std::string &username)
{
	return (socket.connectServ(ip, username));
}

bool Core::run()
{
	joinServer("localhost", "Boudou33");
	while (this->graphique.isOpen())
	{
		graphique.refreshFrame();
	}
	return (true);
}