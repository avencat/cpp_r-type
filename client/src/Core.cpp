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

bool Core::run(const bool &debug)
{
	if (debug) {
		graphique.loadScene(ScenesEnum::InGame);
	}
	while (this->graphique.isOpen() && !this->socket.getInternalError())
	{
		if (graphique.getIp().length() > 0 && graphique.getUsername().length() > 0 && socket.getStatus() == 0) {
			graphique.refreshFrame();
			joinServer(graphique.getIp(), graphique.getUsername());
		} else if (socket.getStatus() == 1) {
			socket.setStatus(0);
			graphique.setIp("");
			graphique.setUsername("");
			graphique.loadPrevScene();
		} else if (socket.getStatus() == 2) {
			socket.setStatus(3);
			graphique.loadNextScene();
		}
		graphique.refreshFrame();
	}
	if (socket.getInternalError()) {
		std::cerr << "The game has been stopped by an internal error. Press ENTER to close this window." << std::endl;
		std::string to_read;
		std::getline(std::cin, to_read);
		return (false);
	}
	return (true);
}
