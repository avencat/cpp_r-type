#ifndef ASOCKET_HPP_
# define ASOCKET_HPP_

# ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#  include <winsock2.h>
#  include <Ws2tcpip.h>
# else
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <arpa/inet.h>
#  include <netdb.h>
#  include <unistd.h>
typedef	int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef ssize_t SSIZE_T;
typedef struct timeval	TIMEVAL;
# endif /* !_WIN32 */
# include <string>
# include <iostream>
#include <sstream>

typedef struct sockaddr SOCKADDR;

class ASocket
{
public:
	ASocket();
	virtual ~ASocket();

	enum SockMode
	{
		UDP,
		TCP
	};

	int				close(SOCKET sock);
	bool			create(const std::string &ip, const u_short port, const SockMode &mode);
	bool			bind();
	// Use these two functions to send data through the socket
	bool			send(const std::stringstream &data, const int &flags = 0);
	bool			sendTo(const std::stringstream &data, const SOCKADDR &from, const socklen_t &fromLen, const int &flags = 0);
	bool			sendTo(const std::stringstream &data, const int &flags = 0);
	// Use these two functions to receive data through the socket
	bool			recv(std::stringstream &data, const size_t &len, const int &flags = 0);
	bool			recvFrom(std::stringstream &data, const size_t &len, SOCKADDR &dest, socklen_t &destLen, const int &flags = 0);
	bool			recvFrom(std::stringstream &data, const size_t &len, const int &flags = 0);
	void			setBlocking(const bool &);
	const u_short	&getPort() const;

private:
#ifdef _WIN32
	WSADATA		wsa_data;
#endif /* !_WIN32 */
	SOCKET		sock;
	SOCKADDR_IN	sin;
	SSIZE_T		lastSentDataLength;
	SSIZE_T		lastRecvDataLength;
	SockMode	mode;
	SOCKADDR	udpAddrFrom;
	socklen_t	fromLen;
	socklen_t	toLen;
	bool		blocking;
	std::string	ip;
	u_short		port;
	fd_set		readfs;
	TIMEVAL		tv;

	int			sockInit();
	int			sockQuit();
};

#endif /* !ASOCKET_HPP_ */

