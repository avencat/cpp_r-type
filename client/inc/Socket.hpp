#ifndef SOCKET_HPP_
# define SOCKET_HPP_

# include <string>
# include "RtypeProtocol.hh"
# include "ASocket.hpp"
# include <ctime>

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
	int					status;
	ASocket				socket;
	std::string			ip;
	void				*data;
	std::size_t			received;
	std::string			username;
	bool				internalError;
};

#endif /* !SOCKET_HPP_ */
