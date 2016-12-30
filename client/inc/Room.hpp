#ifndef ROOM_HPP_
# define ROOM_HPP_

# include "RtypeProtocol.hh"
# include <string>

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
	const bool						&getP1Ready() const;
	const bool						&getP2Ready() const;
	const bool						&getP3Ready() const;
	const bool						&getP4Ready() const;
	std::string						getText() const;
	void							setId(const int &id);
	void							setNbUsers(const int &nbUsers);
	void							setState(const RtypeProtocol::roomState &state);
	void							setPlayer1(const std::string &);
	void							setPlayer2(const std::string &);
	void							setPlayer3(const std::string &);
	void							setPlayer4(const std::string &);
	void							setP1Ready(const bool &);
	void							setP2Ready(const bool &);
	void							setP3Ready(const bool &);
	void							setP4Ready(const bool &);

private:
	int								id;
	int								nbUsers;
	RtypeProtocol::roomState		state;
	std::string						player1;
	std::string						player2;
	std::string						player3;
	std::string						player4;
	bool							p1Ready;
	bool							p2Ready;
	bool							p3Ready;
	bool							p4Ready;
};

#endif // !ROOM_HPP_
