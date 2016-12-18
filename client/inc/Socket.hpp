#ifndef SOCKET_HPP_
# define SOCKET_HPP_

# include <SFML/Network.hpp>
# include <string>
# include "RtypeProtocol.hh"

class Socket
{
public:
	Socket();
	virtual ~Socket();

	bool				connectServ(const std::string &ip, const std::string &_username);
	bool				closeConnection();
	int					getStatus() const;
	void				setStatus(int);
	bool				send(void *dataToSend, const size_t &sizeOfData);
	bool				receive(const size_t &);
	const std::string	&getUsername() const;
	void				setInternalError(const bool &);
	const bool			&getInternalError() const;
	void				*getReceivedData() const;

private:
	unsigned short		port;
	int					status;
	sf::UdpSocket		sendSocket;
	sf::UdpSocket		receiveSocket;
	sf::IpAddress		ip;
	void				*data;
	std::size_t			received;
	sf::SocketSelector	selector;
	std::string			username;
	bool				internalError;
};

#endif /* !SOCKET_HPP_ */
