#ifndef SOCKET_HPP_
# define SOCKET_HPP_

# include <SFML/Network.hpp>
# include <string>

class Socket
{
public:
	Socket();
	virtual ~Socket();

	bool	connectServ(const unsigned short &port, const std::string &ip);
	bool	closeConnection();
	bool	getStatus() const;

private:
	unsigned short	port;
	bool			status;
	sf::UdpSocket	socket;
	sf::IpAddress	ip;
};

#endif /* !SOCKET_HPP_ */
