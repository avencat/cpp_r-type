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
# endif /* !_WIN32 */
# include <string>
# include <iostream>

typedef struct sockaddr SOCKADDR;
typedef struct timeval	TIMEVAL;

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

	int			close(SOCKET sock);
	bool		create(const std::string &ip, const short &port, const SockMode &mode);
	bool		bind();
	// Use these two functions to send data through the socket
	bool		send(const void *data, const size_t &len, const int &flags = 0);
	bool		sendTo(const void *data, const size_t &len, const SOCKADDR &from, const socklen_t &fromLen, const int &flags = 0);
	bool		sendTo(const void *data, const size_t &len, const int &flags = 0);
	// Use these two functions to receive data through the socket
	bool		recv(void *buf, const size_t &len, const int &flags = 0);
	bool		recvFrom(void *buf, const size_t &len, SOCKADDR &dest, socklen_t &destLen, const int &flags = 0);
	bool		recvFrom(void *buf, const size_t &len, const int &flags = 0);
	void		setBlocking(const bool &);
	const short	&getPort() const;

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
	short		port;
	fd_set		readfs;
	TIMEVAL		tv;
	

	int			sockInit();
	int			sockQuit();
};

#endif /* !ASOCKET_HPP_ */

