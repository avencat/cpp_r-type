#ifndef ROOM_HPP_
# define ROOM_HPP_

# include "RtypeProtocol.hh"
# include <String>

class Room
{
public:
	Room();
	Room(int id, int nbUsers, RtypeProtocol::roomState state);
	virtual ~Room();

	const int						&getId() const;
	const int						&getNbUsers() const;
	const RtypeProtocol::roomState	&getState() const;
	const std::string				&getPlayer1() const;
	const std::string				&getPlayer2() const;
	const std::string				&getPlayer3() const;
	const std::string				&getPlayer4() const;
	void							setId(const int &id);
	void							setNbUsers(const int &nbUsers);
	void							setState(const RtypeProtocol::roomState &state);
	void							setPlayer1(const std::string &);
	void							setPlayer2(const std::string &);
	void							setPlayer3(const std::string &);
	void							setPlayer4(const std::string &);

private:
	int								id;
	int								nbUsers;
	RtypeProtocol::roomState		state;
	std::string						player1;
	std::string						player2;
	std::string						player3;
	std::string						player4;
};

#endif // !ROOM_HPP_
