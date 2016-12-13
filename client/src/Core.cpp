#include "..\inc\Core.hpp"

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

bool Core::joinServer(const std::string &ip, const unsigned short &port)
{
	socket.connectServ(port, ip);
	return false;
}

bool Core::run()
{
	while (this->graphique.isOpen())
	{
		graphique.refreshFrame();
	}
	return (true);
}