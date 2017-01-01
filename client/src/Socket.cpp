#include "Socket.hpp"
#include <iostream>

Socket::Socket()
{
	this->internalError = false;
	this->status = 0;
	isInit = false;
}

Socket::~Socket()
{
}

void 			Socket::setBlocking(const bool &blocking)
{
	socket.setBlocking(blocking);
}

std::stringstream	&Socket::getReceivedData()
{
	return (this->receivedData);
}

bool Socket::send(std::stringstream &dataToSend)
{
	if (!isInit) {
		std::cerr << "[Socket Error] You must init the socket before send anything through it!" << std::endl;
		return (false);
	}
	if (!socket.sendTo(dataToSend)) {
		RtypeProtocol::Data::Code	code;

		dataToSend.read(reinterpret_cast<char *>(&(code.code)), sizeof(code.code));
		std::cerr << "[INTERNAL ERROR] Couldn't send message :\"" << code.code << "\" to " << ip << ":" << socket.getPort() << std::endl;
		return (false);
	}
	return (true);
}

bool Socket::receive(const size_t &sizeToReceive, const bool &showError)
{
	if (!isInit) {
		if (showError)
			std::cerr << "[Socket Error] You must init the socket before send anything through it!" << std::endl;
		return (false);
	}
	receivedData.str("");
	if (!this->socket.recvFrom(receivedData, sizeToReceive))
	{
		if (showError)
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
	RtypeProtocol::Data::Handshake	syn;
	RtypeProtocol::Data::Username	username;
	std::stringstream		receivedCpy;

	socket.create(_ip, 42142, ASocket::SockMode::UDP);
	isInit = true;
	socket.bind();
	this->username = _username;
	this->ip = _ip;
	this->status = 1;
	this->socket.setBlocking(true);
	syn.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::SYN);
	srand(time(NULL));
	syn.syn = rand();
	syn.ack = 0;
	sentData.str("");
	sentData.write(reinterpret_cast<char *>(&(syn.code)), sizeof(syn.code));
	sentData.write(reinterpret_cast<char *>(&(syn.syn)), sizeof(syn.syn));
	sentData.write(reinterpret_cast<char *>(&(syn.ack)), sizeof(syn.ack));
	if (!socket.sendTo(sentData))
	{
		std::cerr << "[INTERNAL ERROR] Couldn't send message :\"SYN\" to " << ip << ":" << socket.getPort() << std::endl;
		return (false);
	}
	if (!socket.recvFrom(receivedData, sizeof(syn.code) + sizeof(syn.syn) + sizeof(syn.ack)))
	{
		std::cerr << "[TIMEOUT] Couldn't receive message from " << ip << ":" << socket.getPort() << std::endl;
		return (false);
	}
	syn.code = 0;
	syn.ack = 0;
	syn.syn = 0;
	receivedData.read(reinterpret_cast<char *>(&(syn.code)), sizeof(syn.code));
	if (syn.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::SYN_ACK)) {
		syn.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::ACK);
		receivedData.read(reinterpret_cast<char *>(&(syn.syn)), sizeof(syn.syn));
		receivedData.read(reinterpret_cast<char *>(&(syn.ack)), sizeof(syn.ack));
		syn.ack += 1;
	} else {
		std::cerr << "Server didn't accept you." << std::endl;
		return (false);
	}
	sentData.str("");
	sentData.write(reinterpret_cast<char *>(&(syn.code)), sizeof(syn.code));
	sentData.write(reinterpret_cast<char *>(&(syn.syn)), sizeof(syn.syn));
	sentData.write(reinterpret_cast<char *>(&(syn.ack)), sizeof(syn.ack));
	if (!this->socket.sendTo(sentData))
	{
		std::cerr << "[INTERNAL ERROR] Couldn't send message :\"SYN\" to " << ip << ":" << socket.getPort() << std::endl;
		return (false);
	}
	if (!this->socket.recvFrom(receivedData, sizeof(syn.code) + sizeof(syn.syn) + sizeof(syn.ack)))
	{
		std::cerr << "[TIMEOUT] Couldn't receive message from " << ip << ":" << socket.getPort() << std::endl;
		return (false);
	}
	receivedData.read(reinterpret_cast<char *>(&(syn.code)), sizeof(syn.code));
	if (syn.code != RtypeProtocol::convertShort(RtypeProtocol::serverCodes::Accepted)) {
		std::cerr << "Server didn't accept you." << std::endl;
		return (false);
	}
	username.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::Username);
	for (unsigned short i = 0; i < (_username.length() < 12 ? _username.length() : 12); i++)
		username.username[i] = _username.c_str()[i];
	sentData.str("");
	sentData.write(reinterpret_cast<char *>(&(username.code)), sizeof(username.code));
	sentData.write(reinterpret_cast<char *>(&(username.username)), sizeof(username.username));
	if (!socket.sendTo(sentData))
	{
		std::cerr << "[INTERNAL ERROR] Couldn't send message :\"USERNAME\" to " << ip << ":" << socket.getPort() << std::endl;
		return (false);
	}
	if (!socket.recvFrom(receivedData, sizeof(RtypeProtocol::Data::Room::code) + sizeof(RtypeProtocol::Data::Room::players) +
		       sizeof(RtypeProtocol::Data::Room::roomID) + sizeof(RtypeProtocol::Data::Room::state)))
	{
		std::cerr << "[TIMEOUT] Couldn't receive message from " << ip << ":" << socket.getPort() << std::endl;
		return (false);
	}
	receivedCpy.str(receivedData.str());
	receivedCpy.read(reinterpret_cast<char *>(&(username.code)), sizeof(username.code));
	if (username.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrInvalidName)) {
		std::cerr << "Server didn't accept you. (Bad Username)" << std::endl;
		return (false);
	}
	this->status = 2;
	socket.setBlocking(false);
	code = username.code;
	return (true);
}

bool Socket::closeConnection()
{
	RtypeProtocol::Data::Code code;

	code.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::PlayerLeave);
	sentData.str("");
	sentData.write(reinterpret_cast<char *>(&(code.code)), sizeof(code.code));
	if (socket.sendTo(sentData))
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
