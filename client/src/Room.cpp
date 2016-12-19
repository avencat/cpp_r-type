#include "Room.hpp"

Room::Room()
{
}

Room::Room(int id, int nbUsers, RtypeProtocol::roomState state)
{
	this->id = id;
	this->nbUsers = nbUsers;
	this->state = state;
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