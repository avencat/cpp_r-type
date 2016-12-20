#include "Room.hpp"

Room::Room()
{
	this->state = RtypeProtocol::roomState::Waiting;
	this->nbUsers = 0;
	this->id = 0;
	this->p1Ready = false;
	this->p2Ready = false;
	this->p3Ready = false;
	this->p4Ready = false;
}

Room::Room(int id, int nbUsers, RtypeProtocol::roomState state)
{
	this->id = id;
	this->nbUsers = nbUsers;
	this->state = state;
	this->p1Ready = false;
	this->p2Ready = false;
	this->p3Ready = false;
	this->p4Ready = false;
}

Room::~Room()
{
}

const int &Room::getId() const
{
	return id;
}

const int &Room::getNbUsers() const
{
	return nbUsers;
}

const RtypeProtocol::roomState &Room::getState() const
{
	return (state);
}

const std::string &Room::getPlayer1() const
{
	return (this->player1);
}

const std::string &Room::getPlayer2() const
{
	return (this->player2);
}

const std::string &Room::getPlayer3() const
{
	return (this->player3);
}

const std::string &Room::getPlayer4() const
{
	return (this->player4);
}

const bool &Room::getP1Ready() const
{
	return (this->p1Ready);
}

const bool &Room::getP2Ready() const
{
	return (this->p2Ready);
}

const bool &Room::getP3Ready() const
{
	return (this->p3Ready);
}

const bool &Room::getP4Ready() const
{
	return (this->p4Ready);
}

std::string	Room::getText() const
{
	std::string	mode;

	switch (this->state)
	{
	case RtypeProtocol::roomState::Full:
		mode = " [Full]";
		break;
	case RtypeProtocol::roomState::Playing:
		mode = " [In game]";
		break;
	case RtypeProtocol::roomState::Waiting:
		mode = " [Waiting]";
		break;
	default:
		break;
	}
	return std::string("Room " + std::to_string(this->id) + "\t" + std::to_string(this->nbUsers) + "p\t" + mode);
}

void Room::setId(const int &id)
{
	this->id = id;
}

void Room::setNbUsers(const int &nbUsers)
{
	this->nbUsers = nbUsers;
}

void Room::setState(const RtypeProtocol::roomState &state)
{
	this->state = state;
}

void Room::setPlayer1(const std::string &playerName)
{
	player1 = playerName;
}

void Room::setPlayer2(const std::string &playerName)
{
	player2 = playerName;
}

void Room::setPlayer3(const std::string &playerName)
{
	player3 = playerName;
}

void Room::setPlayer4(const std::string &playerName)
{
	player4 = playerName;
}

void Room::setP1Ready(const bool &ready)
{
	this->p1Ready = ready;
}

void Room::setP2Ready(const bool &ready)
{
	this->p2Ready = ready;
}

void Room::setP3Ready(const bool &ready)
{
	this->p3Ready = ready;
}

void Room::setP4Ready(const bool &ready)
{
	this->p4Ready = ready;
}
