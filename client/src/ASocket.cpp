#include "ASocket.hpp"

ASocket::ASocket()
{
	fromLen = sizeof(udpAddrFrom);
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

int ASocket::sockClose(SOCKET sock)
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

bool ASocket::sockCreate(const std::string &ip, const short &port, const ASocket::SockMode &mode)
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

bool ASocket::sockBind()
{
	if (bind(sock, (SOCKADDR *)&sin, sizeof(sin)) != 0)
		return (false);
	return (true);
}

bool ASocket::sockSend(const void *data, const size_t &len, const int &flags)
{
#ifdef _WIN32
	if (mode == SockMode::TCP)
		lastSentDataLength = send(sock, reinterpret_cast<const char *>(data), len, flags);
	else
		lastSentDataLength = sendto(sock, reinterpret_cast<const char *>(data), len, flags, reinterpret_cast<SOCKADDR *>(&sin), toLen);
#else
	if (mode == SockMode::TCP)
		lastSentDataLength = send(sock, data, len, flags);
	else
		lastSentDataLength = sendto(sock, data, len, flags, reinterpret_cast<SOCKADDR *>(&sin), toLen);
#endif /* !_WIN32 */

	return (lastSentDataLength > 0 || len == 0);
}

bool ASocket::sockRecv(void *buf, const size_t & len, const int &flags)
{
#ifdef _WIN32
	if (mode == SockMode::TCP)
		lastRecvDataLength = recv(sock, reinterpret_cast<char *>(buf), len, flags);
	else
		lastRecvDataLength = recvfrom(sock, reinterpret_cast<char *>(buf), len, flags, &udpAddrFrom, &fromLen);
#else
	if (mode == SockMode::TCP)
		lastRecvDataLength = recv(sock, buf, len, flags);
	else
		lastRecvDataLength = recvfrom(sock, buf, len, flags, &udpaddrfrom, &fromlen);
#endif /* !_WIN32 */
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

