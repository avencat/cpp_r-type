#include "Socket.hpp"
#include <iostream>

Socket::Socket()
{
	this->port = 42142;
	if (this->receiveSocket.bind(this->port) != sf::Socket::Done)
	{
		std::cerr << "[INTERNAL ERROR] Couldn't bind the port " << this->port << std::endl;
	}
}

Socket::~Socket()
{
}

bool Socket::connectServ(const std::string &_ip, const std::string &_username)
{
	std::size_t						received;
	RtypeProtocol::Data::Handshake	*syn;
	RtypeProtocol::Data::Username	*username;
	void							*data;
	sf::SocketSelector				selector;

	this->ip = _ip;
	this->status = 1;
	this->sendSocket.setBlocking(true);
	this->receiveSocket.setBlocking(true);
	syn = new RtypeProtocol::Data::Handshake;
	syn->code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::SYN);
	syn->syn = rand() % 4242;
	syn->ack = 0;
	selector.add(receiveSocket);
	if (this->sendSocket.send(syn, sizeof(RtypeProtocol::Data::Handshake), this->ip, this->port) != sf::Socket::Done)
	{
		std::cerr << "[INTERNAL ERROR] Couldn't send message :\"SYN\" to " << ip << ":" << port << std::endl;
		delete syn;
		return (false);
	}
	data = new char[100];
	memset(data, 0, 100);
	if (selector.wait(sf::seconds(3))) {
		if (this->receiveSocket.receive(data, sizeof(RtypeProtocol::Data::Handshake), received, ip, port) != sf::Socket::Done)
		{
			std::cerr << "[INTERNAL ERROR] Couldn't receive message from " << ip << ":" << port << std::endl;
			delete syn;
			delete data;
			return (false);
		}
	} else {
		std::cerr << "[TIMEOUT] Couldn't receive message from " << ip << ":" << port << std::endl;
		delete syn;
		delete data;
		return (false);
	}
	std::cout << reinterpret_cast<RtypeProtocol::Data::Handshake *>(data)->code << std::endl;
	std::cout << "Received " << received << " bytes from " << ip << " on port " << port << " (" << data << ")" << std::endl;
	if (reinterpret_cast<RtypeProtocol::Data::Handshake *>(data)->code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::SYN_ACK)) {
		syn->code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::ACK);
		syn->ack = reinterpret_cast<RtypeProtocol::Data::Handshake *>(data)->ack + 1;
		syn->syn = 0;
	} else {
		delete syn;
		delete data;
		return (false);
	}
	if (this->sendSocket.send(syn, sizeof(RtypeProtocol::Data::Handshake), this->ip, this->port) != sf::Socket::Done)
	{
		std::cerr << "[INTERNAL ERROR] Couldn't send message :\"SYN\" to " << ip << ":" << port << std::endl;
		delete syn;
		delete data;
		return (false);
	}
	memset(data, 0, 100);
	if (selector.wait(sf::seconds(3))) {
		if (this->receiveSocket.receive(data, sizeof(RtypeProtocol::Data::Handshake), received, ip, port) != sf::Socket::Done)
		{
			std::cerr << "[INTERNAL ERROR] Couldn't receive message from " << ip << ":" << port << std::endl;
			delete syn;
			delete data;
			return (false);
		}
	} else {
		std::cerr << "[TIMEOUT] Couldn't receive message from " << ip << ":" << port << std::endl;
		delete syn;
		delete data;
		return (false);
	}
	std::cout << reinterpret_cast<RtypeProtocol::Data::Handshake *>(data)->code << std::endl;
	std::cout << "Received " << received << " bytes from " << ip << " on port " << port << " (" << data << ")" << std::endl;
	if (reinterpret_cast<RtypeProtocol::Data::Handshake *>(data)->code != RtypeProtocol::convertShort(RtypeProtocol::serverCodes::Accepted)) {
		std::cerr << "Server didn't accept you." << std::endl;
		delete syn;
		delete data;
		return (false);
	}
	delete syn;
	username = new RtypeProtocol::Data::Username;
	username->code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::Username);
	for (short i = 0; i < (_username.length() < 12 ? _username.length() : 12); i++)
		username->username[i] = _username.c_str()[i];
	if (this->sendSocket.send(username, sizeof(RtypeProtocol::Data::Username), this->ip, this->port) != sf::Socket::Done)
	{
		std::cerr << "[INTERNAL ERROR] Couldn't send message :\"USERNAME\" to " << ip << ":" << port << std::endl;
		delete username;
		delete data;
		return (false);
	}
	delete username;
	delete data;
	return (true);
}

bool Socket::closeConnection()
{
	if (this->sendSocket.send("105", 3, ip, port))
	{
		std::cerr << "Couldn't tell the server that we left." << std::endl;
		return (false);
	}
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
