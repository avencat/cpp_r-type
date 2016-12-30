#include "ASocket.hpp"

ASocket::ASocket()
{
	fromLen = sizeof(udpAddrFrom);
	tv.tv_sec = 3;
	tv.tv_usec = 0;
	blocking = true;
}

ASocket::~ASocket()
{
}

int ASocket::sockInit()
{
#ifdef _WIN32
	return WSAStartup(MAKEWORD(2, 1), &wsa_data);
#else
	return (0);
#endif
}

int ASocket::sockQuit()
{
#ifdef _WIN32
	return WSACleanup();
#else
	return 0;
#endif
}

int ASocket::close(SOCKET _sock)
{
	int status = 0;

#ifdef _WIN32
	status = shutdown(_sock, SD_BOTH);
	if (status == 0) {
		status = closesocket(_sock);
	}
	return (sockQuit());
#else
	status = shutdown(_sock, SHUT_RDWR);
	if (status == 0) {
		status = close(_sock);
	}
#endif

	return (status);
}

bool ASocket::create(const std::string &_ip, const u_short &_port, const ASocket::SockMode &_mode)
{
	sockInit();
	this->mode = _mode;
	this->port = _port;
	this->ip = _ip;
	sin.sin_addr.s_addr = inet_addr(_ip.c_str());
	sin.sin_family = AF_INET;
	sin.sin_port = htons(_port);
	toLen = sizeof(sin);
	sock = socket(AF_INET, _mode == ASocket::SockMode::TCP ? SOCK_STREAM : SOCK_DGRAM, 0);
	if (sock == -1)
		return (false);
	return (true);
}

bool ASocket::bind()
{
	if (::bind(sock, (SOCKADDR *)&sin, sizeof(sin)) != 0)
		return (false);
	return (true);
}

bool ASocket::send(const std::stringstream &data, const int &flags)
{
#ifdef _WIN32
	if (mode == SockMode::TCP)
		lastSentDataLength = ::send(sock, data.str().c_str(), data.str().length(), flags);
	else
		return(sendTo(data, flags));
#else
	if (mode == SockMode::TCP)
		lastSentDataLength = ::send(sock, reinterpret_cast<void *>(data.str().c_str()), data.str().length(), flags);
	else
		sendTo(data, flags);
#endif /* !_WIN32 */

	return (lastSentDataLength > 0 || data.str().length() == 0);
}

bool ASocket::sendTo(const std::stringstream &data, const SOCKADDR &from, const socklen_t &_fromLen, const int &flags)
{
	if (mode != SockMode::UDP)
		return (false);
#ifdef _WIN32
	lastSentDataLength = ::sendto(sock, data.str().c_str(), data.str().length(), flags, reinterpret_cast<const SOCKADDR *>(&from), _fromLen);
#else
	lastSentDataLength = ::sendto(sock, reinterpret_cast<const void *>(data.str().c_str()), data.str().length(), flags, reinterpret_cast<const SOCKADDR *>(&from), _fromLen);
#endif /* !_WIN32 */
	return (lastSentDataLength > 0 || data.str().length() == 0);
}

bool ASocket::sendTo(const std::stringstream &data, const int &flags)
{
	if (mode != SockMode::UDP)
		return (this->send(data, flags));
#ifdef _WIN32
	lastSentDataLength = ::sendto(sock, data.str().c_str(), data.str().length(), flags, reinterpret_cast<SOCKADDR *>(&sin), toLen);
	if (lastSentDataLength == SOCKET_ERROR) {
		std::cerr << lastSentDataLength << " && " << WSAGetLastError() << std::endl;
	}
#else
	lastSentDataLength = ::sendto(sock, reinterpret_cast<const void *>(data.str().c_str()), data.str().length(), flags, reinterpret_cast<SOCKADDR *>(&sin), toLen);
#endif /* !_WIN32 */
	return (lastSentDataLength > 0 || data.str().length() == 0);
}

bool ASocket::recv(std::stringstream &data, const size_t &len, const int &flags)
{
	int		ret;
	char	buf[100];

	if (this->mode == SockMode::UDP)
		return (this->recvFrom(data, len, flags));
	FD_ZERO(&readfs);
	FD_SET(sock, &readfs);
	if (!blocking) {
		if ((ret = select(sock + 1, &readfs, NULL, NULL, 0)) < 0) {
			perror("select()");
			return (false);
		}

		if (ret == 0) {
			return (false);
		}
	} else {
		if ((ret = select(sock + 1, &readfs, NULL, NULL, 0)) < 0) {
			perror("select()");
			return (false);
		}

		if (ret == 0) {
			return (false);
		}
	}
	if (FD_ISSET(sock, &readfs)) {
#ifdef _WIN32
		lastRecvDataLength = ::recv(sock, buf, len, flags);
#else
		lastRecvDataLength = ::recv(sock, reinterpret_cast<void *>(buf), len, flags);
#endif /* !_WIN32 */
	}
	data.str(buf);
	return (lastRecvDataLength != -1);
}

bool ASocket::recvFrom(std::stringstream &data, const size_t &len, SOCKADDR &dest, socklen_t &destLen, const int &flags)
{
	int		ret;
	char	buf[100];

	if (mode == SockMode::TCP) {
		std::cerr << "You can't use recvFrom with an UDP socket." << std::endl;
		return (false);
	}
	FD_ZERO(&readfs);
	FD_SET(sock, &readfs);
	if (!blocking) {
		std::cout << "!blocking" << std::endl;
		if ((ret = select(sock + 1, &readfs, NULL, NULL, 0)) < 0) {
			perror("select()");
			return (false);
		}

		if (ret == 0) {
			return (false);
		}
	} else {
		if ((ret = select(sock + 1, &readfs, NULL, NULL, &tv)) < 0) {
			perror("select()");
			return (false);
		}

		if (ret == 0) {
			return (false);
		}
	}
	if (FD_ISSET(sock, &readfs)) {
#ifdef _WIN32
		lastRecvDataLength = ::recvfrom(sock, reinterpret_cast<char *>(buf), len, flags, &dest, &destLen);
#else
		lastRecvDataLength = ::recvfrom(sock, reinterpret_cast<void *>(buf), len, flags, &dest, &destLen);
#endif /* !_WIN32 */
	}
	data.str(buf);
	return (lastRecvDataLength != -1);
}

bool ASocket::recvFrom(std::stringstream &data, const size_t &len, const int &flags)
{
	int		ret;
	char	buf[100];

	if (mode == SockMode::TCP) {
		return (this->recv(data, len, flags));
	}
	FD_ZERO(&readfs);
	FD_SET(sock, &readfs);
	if (!blocking) {
		if ((ret = select(sock + 1, &readfs, NULL, NULL, 0)) < 0) {
			std::cerr << "! ret = " << ret << std::endl;
			perror("select()");
			return (false);
		}

		if (ret == 0) {
			return (false);
		}
	} else {
		if ((ret = select(sock, &readfs, NULL, NULL, &tv)) < 0) {
			std::cerr << "ret = " << ret << std::endl;
			perror("select()");
			return (false);
		}

		if (ret == 0) {
			return (false);
		}
	}
	if (FD_ISSET(sock, &readfs)) {
#ifdef _WIN32
		lastRecvDataLength = ::recvfrom(sock, reinterpret_cast<char *>(buf), len, flags, &udpAddrFrom, &fromLen);
#else
		lastRecvDataLength = ::recvfrom(sock, reinterpret_cast<void *>(buf), len, flags, &udpAddrFrom, &fromlen);
#endif /* !_WIN32 */
	}
	data.str(buf);
	return (lastRecvDataLength != -1);
}
 
void ASocket::setBlocking(const bool &block)
{
	blocking = block;
}

const u_short &ASocket::getPort() const
{
	return (this->port);
}

