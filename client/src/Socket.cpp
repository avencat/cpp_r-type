#include "..\inc\Socket.hpp"

Socket::Socket()
{
}

Socket::~Socket()
{
}

bool Socket::connectServ(const unsigned short & port, const std::string & ip)
{
	return false;
}

bool Socket::closeConnection()
{
	return false;
}

bool Socket::getStatus() const
{
	return (this->status);
}
