#ifndef SOCKET_HPP_
# define SOCKET_HPP_

# include <string>
# include "RtypeProtocol.hh"
# include "ASocket.hpp"
# include <ctime>
# include <sstream>

class Socket
{
public:
	Socket();
	virtual ~Socket();

	bool				connectServ(const std::string &ip, const std::string &_username);
	bool				closeConnection();
	int					getStatus() const;
	void				setStatus(int);
	bool				send(std::stringstream &dataToSend);
	bool				receive(const size_t &, const bool &showError = true);
	const std::string	&getUsername() const;
	void				setInternalError(const bool &);
	const bool			&getInternalError() const;
	std::stringstream	&getReceivedData();
	void 			setBlocking(const bool &);

private:
	int					status;
	ASocket				socket;
	std::string			ip;
	std::stringstream	receivedData;
	std::stringstream	sentData;
	std::string			username;
	bool				internalError;
	bool				isInit;
	int				code;
};

#endif /* !SOCKET_HPP_ */
