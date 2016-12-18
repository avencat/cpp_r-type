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

	bool	connectServ(const std::string &ip, const std::string &_username);
	bool	closeConnection();
	int		getStatus() const;
	void    setStatus(int);

private:
	unsigned short	port;
	int				status;
	sf::UdpSocket	sendSocket;
	sf::UdpSocket	receiveSocket;
	sf::IpAddress	ip;
};

#endif /* !SOCKET_HPP_ */
