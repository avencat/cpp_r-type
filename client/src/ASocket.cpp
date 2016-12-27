#include "ASocket.hpp"

ASocket::ASocket()
{
	fromLen = sizeof(udpAddrFrom);
	tv.tv_sec = 3;
	tv.tv_usec = 0;
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

int ASocket::close(SOCKET sock)
{
	int status = 0;

#ifdef _WIN32
	status = shutdown(sock, SD_BOTH);
	if (status == 0) {
		status = closesocket(sock);
	}
	return (sockQuit());
#else
	status = shutdown(sock, SHUT_RDWR);
	if (status == 0) {
		status = close(sock);
	}
#endif

	return (status);
}

bool ASocket::create(const std::string &ip, const short &port, const ASocket::SockMode &mode)
{
	sockInit();
	this->port = port;
	this->ip = ip;
	sin.sin_addr.s_addr = inet_addr(ip.c_str());
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	toLen = sizeof(sin);
	sock = socket(AF_INET, mode == ASocket::SockMode::TCP ? SOCK_STREAM : SOCK_DGRAM, 0);
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

bool ASocket::send(const void *data, const size_t &len, const int &flags)
{
#ifdef _WIN32
	if (mode == SockMode::TCP)
		lastSentDataLength = ::send(sock, reinterpret_cast<const char *>(data), len, flags);
	else
		return(sendTo(data, len, flags));
#else
	if (mode == SockMode::TCP)
		lastSentDataLength = ::send(sock, data, len, flags);
	else
		sendTo(data, len, flags);
#endif /* !_WIN32 */

	return (lastSentDataLength > 0 || len == 0);
}

bool ASocket::sendTo(const void *data, const size_t &len, const SOCKADDR &from, const socklen_t &fromLen, const int &flags)
{
	if (mode != SockMode::UDP)
		return (false);
#ifdef _WIN32
	lastSentDataLength = ::sendto(sock, reinterpret_cast<const char *>(data), len, flags, reinterpret_cast<const SOCKADDR *>(&from), fromLen);
#else
	lastSentDataLength = ::sendto(sock, data, len, flags, reinterpret_cast<const SOCKADDR *>(&from), fromLen);
#endif /* !_WIN32 */
	return (lastSentDataLength > 0 || len == 0);
}

bool ASocket::sendTo(const void *data, const size_t &len, const int &flags)
{
	if (mode != SockMode::UDP)
		return (this->send(data, len, flags));
#ifdef _WIN32
	lastSentDataLength = ::sendto(sock, reinterpret_cast<const char *>(data), len, flags, reinterpret_cast<SOCKADDR *>(&sin), toLen);
#else
	lastSentDataLength = ::sendto(sock, data, len, flags, reinterpret_cast<SOCKADDR *>(&sin), toLen);
#endif /* !_WIN32 */
	return (lastSentDataLength > 0 || len == 0);
}

bool ASocket::recv(void *buf, const size_t &len, const int &flags)
{
	int		ret;

	if (this->mode == SockMode::UDP)
		return (this->recvFrom(buf, len, flags));
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
		lastRecvDataLength = ::recv(sock, reinterpret_cast<char *>(buf), len, flags);
#else
		lastRecvDataLength = ::recv(sock, buf, len, flags);
#endif /* !_WIN32 */
		return (lastRecvDataLength != -1);
	}
	return (lastRecvDataLength != -1);
}

bool ASocket::recvFrom(void *buf, const size_t &len, SOCKADDR &dest, socklen_t &destLen, const int &flags)
{
	int		ret;

	if (mode == SockMode::TCP) {
		std::cerr << "You can't use recvFrom with an UDP socket." << std::endl;
		return (false);
	}
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
		lastRecvDataLength = ::recvfrom(sock, buf, len, flags, &dest, &destLen);
#endif /* !_WIN32 */
	}
	return (lastRecvDataLength != -1);
}

bool ASocket::recvFrom(void *buf, const size_t &len, const int &flags)
{
	int		ret;

	if (mode == SockMode::TCP) {
		return (this->recv(buf, len, flags));
	}
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
		lastRecvDataLength = ::recvfrom(sock, reinterpret_cast<char *>(buf), len, flags, &udpAddrFrom, &fromLen);
#else
		lastRecvDataLength = ::recvfrom(sock, buf, len, flags, &udpaddrfrom, &fromlen);
#endif /* !_WIN32 */
	}
	return (lastRecvDataLength != -1);
}
 
void ASocket::setBlocking(const bool &block)
{
	blocking = block;
}

const short & ASocket::getPort() const
{
	return (this->port);
}

