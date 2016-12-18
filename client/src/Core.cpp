#include "Core.hpp"

Core::Core(const int &_x, const int &_y, const std::string &_title) : graphique(socket, _x, _y, _title)
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
	while (this->graphique.isOpen() && !this->socket.getInternalError())
	{
		if (graphique.getIp().length() > 0 && graphique.getUsername().length() > 0 && socket.getStatus() == 0) {
			graphique.refreshFrame();
			joinServer(graphique.getIp(), graphique.getUsername());
		} else {
			socket.setStatus(0);
			graphique.setIp("");
			graphique.setUsername("");
			graphique.loadPrevScene();
		}
		graphique.refreshFrame();
	}
	return (true);
}