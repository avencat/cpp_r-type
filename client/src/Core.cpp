#include "..\inc\Core.hpp"
#pragma once

Core::Core(const int &_x, const int &_y, const std::string &_title) : graphique(_x, _y, _title)
{
}

Core::~Core()
{
}

const bool Core::isUp() const
{
	return (this->run);
}

bool Core::joinServer(const std::string &ip, const unsigned short &port)
{
	socket.connectServ(port, ip);
	return false;
}
