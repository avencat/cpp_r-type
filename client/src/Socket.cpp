#include "Socket.hpp"
#include <iostream>

Socket::Socket()
{
	data = new char[100];
	this->internalError = false;
	this->status = 0;
}

Socket::~Socket()
{
	delete[] data;
}

void	*Socket::getReceivedData() const
{
	return (this->data);
}

bool Socket::send(void *dataToSend, const size_t &sizeOfData)
{
	if (!socket.sockSend(dataToSend, sizeOfData)) {
		std::cerr << "[INTERNAL ERROR] Couldn't send message :\"" << reinterpret_cast<RtypeProtocol::Data::Code *>(data)->code << "\" to " << ip << ":" << socket.getPort() << std::endl;
		return (false);
	}
	return (true);
}

bool Socket::receive(const size_t &sizeToReceive)
{
	memset(data, 0, 100);
	if (!this->socket.sockRecv(data, sizeToReceive))
	{
		std::cerr << "[INTERNAL ERROR] Couldn't receive message from " << ip << ":" << socket.getPort() << std::endl;
		return (false);
	} else {
		std::cerr << "[TIMEOUT] Couldn't receive message from " << ip << ":" << socket.getPort() << std::endl;
		return (false);
	}
	return (true);
}

const std::string	&Socket::getUsername() const
{
	return (this->username);
}

void	Socket::setInternalError(const bool &intErr)
{
	this->internalError = intErr;
}

const bool & Socket::getInternalError() const
{
	return (this->internalError);
}

bool Socket::connectServ(const std::string &_ip, const std::string &_username)
{
	std::size_t						received;
	RtypeProtocol::Data::Handshake	*syn;
	RtypeProtocol::Data::Username	*username;

	socket.sockCreate(_ip, 42142, ASocket::SockMode::UDP);
	this->username = _username;
	this->ip = _ip;
	this->status = 1;
	// Delete this line
	this->status = 2;
	// Delete the line before this line
	this->socket.setBlocking(true);
	syn = new RtypeProtocol::Data::Handshake;
	syn->code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::SYN);
	srand(time(NULL));
	syn->syn = rand();
	syn->ack = 0;
	if (!socket.sockSend(syn, sizeof(RtypeProtocol::Data::Handshake)))
	{
		std::cerr << "[INTERNAL ERROR] Couldn't send message :\"SYN\" to " << ip << ":" << socket.getPort() << std::endl;
		delete syn;
		return (false);
	}
	std::cout << "Sent message to " << this->ip << ":" << socket.getPort() << std::endl;
	memset(data, 0, 100);
	if (!socket.sockRecv(data, sizeof(RtypeProtocol::Data::Handshake)))
	{
		std::cerr << "[INTERNAL ERROR] Couldn't receive message from " << ip << ":" << socket.getPort() << std::endl;
		delete syn;
		return (false);
	} else {
		std::cerr << "[TIMEOUT] Couldn't receive message from " << ip << ":" << socket.getPort() << std::endl;
		delete syn;
		return (false);
	}
	std::cout << reinterpret_cast<RtypeProtocol::Data::Handshake *>(data)->code << std::endl;
	std::cout << "Received " << received << " bytes from " << ip << " on port " << socket.getPort() << " (" << data << ")" << std::endl;
	if (reinterpret_cast<RtypeProtocol::Data::Handshake *>(data)->code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::SYN_ACK)) {
		syn->code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::ACK);
		syn->ack = reinterpret_cast<RtypeProtocol::Data::Handshake *>(data)->ack + 1;
		syn->syn = 0;
	} else {
		delete syn;
		return (false);
	}
	if (!this->socket.sockSend(syn, sizeof(RtypeProtocol::Data::Handshake)))
	{
		std::cerr << "[INTERNAL ERROR] Couldn't send message :\"SYN\" to " << ip << ":" << socket.getPort() << std::endl;
		delete syn;
		return (false);
	}
	memset(data, 0, 100);
	if (!this->socket.sockRecv(data, sizeof(RtypeProtocol::Data::Handshake)))
	{
		std::cerr << "[INTERNAL ERROR] Couldn't receive message from " << ip << ":" << socket.getPort() << std::endl;
		delete syn;
		return (false);
	} else {
		std::cerr << "[TIMEOUT] Couldn't receive message from " << ip << ":" << socket.getPort() << std::endl;
		delete syn;
		return (false);
	}
	std::cout << reinterpret_cast<RtypeProtocol::Data::Handshake *>(data)->code << std::endl;
	std::cout << "Received " << received << " bytes from " << ip << " on port " << socket.getPort() << " (" << data << ")" << std::endl;
	if (reinterpret_cast<RtypeProtocol::Data::Handshake *>(data)->code != RtypeProtocol::convertShort(RtypeProtocol::serverCodes::Accepted)) {
		std::cerr << "Server didn't accept you." << std::endl;
		delete syn;
		return (false);
	}
	delete syn;
	username = new RtypeProtocol::Data::Username;
	username->code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::Username);
	for (short i = 0; i < (_username.length() < 12 ? _username.length() : 12); i++)
		username->username[i] = _username.c_str()[i];
	if (socket.sockSend(username, sizeof(RtypeProtocol::Data::Username)))
	{
		std::cerr << "[INTERNAL ERROR] Couldn't send message :\"USERNAME\" to " << ip << ":" << socket.getPort() << std::endl;
		delete username;
		return (false);
	}
	memset(data, 0, 100);
	if (socket.sockRecv(data, sizeof(RtypeProtocol::Data::Username)))
	{
		std::cerr << "[INTERNAL ERROR] Couldn't receive message from " << ip << ":" << socket.getPort() << std::endl;
		delete syn;
		return (false);
	}
	else {
		std::cerr << "[TIMEOUT] Couldn't receive message from " << ip << ":" << socket.getPort() << std::endl;
		delete syn;
		return (false);
	}
	std::cout << reinterpret_cast<RtypeProtocol::Data::RoomBegin *>(data)->code << std::endl;
	std::cout << "Received " << received << " bytes from " << ip << " on port " << socket.getPort() << " (" << data << ")" << std::endl;
	if (reinterpret_cast<RtypeProtocol::Data::RoomBegin *>(data)->code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrInvalidName)) {
		std::cerr << "Server didn't accept you. (Bad Username)" << std::endl;
		delete username;
		return (false);
	}
	delete username;
	this->status = 2;
	return (true);
}

bool Socket::closeConnection()
{
	RtypeProtocol::Data::Code *code;

	code = new RtypeProtocol::Data::Code;
	code->code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::PlayerLeave);
	if (socket.sockSend(code, 3))
	{
		std::cerr << "Couldn't tell the server that we left." << std::endl;
		delete code;
		return (false);
	}
	delete code;
	return (true);
}

int Socket::getStatus() const
{
	return (this->status);
}

void Socket::setStatus(int st)
{
	this->status = st;
}
