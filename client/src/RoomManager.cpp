#include "RoomManager.hpp"

RoomManager::RoomManager(Socket &socket) : socket(socket)
{
	listRooms.push_back(Room(1, 2, RtypeProtocol::roomState::Waiting));
	listRooms.push_back(Room(2, 2, RtypeProtocol::roomState::Waiting));
	listRooms.push_back(Room(3, 3, RtypeProtocol::roomState::Playing));
	listRooms.push_back(Room(4, 4, RtypeProtocol::roomState::Full));
	listRooms.push_back(Room(12, 3, RtypeProtocol::roomState::Waiting));
	currentRoom = listRooms.front();
	currentRoom.setNbUsers(3);
	currentRoom.setPlayer1("Th�o");
	currentRoom.setPlayer2("Louis");
	currentRoom.setPlayer3("Axel");
	currentRoom.setP1Ready(true);
	currentRoom.setP2Ready(true);
	currentRoom.setP3Ready(false);
	gameStarted = false;
}

RoomManager::~RoomManager()
{
}

const Room	&RoomManager::getCurrentRoom()
{
	return (currentRoom);
}

bool								RoomManager::ready()
{
	RtypeProtocol::Data::Code		code;

	code.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::RoomReady);
	sentData.str("");
	sentData.write(reinterpret_cast<char *>(&(code.code)), sizeof(code.code));
	if (socket.send(sentData) == false) {
		return (false);
	}
	if (socket.receive(sizeof(RtypeProtocol::Data::RoomInfo)) == false)
		return (false);
	manageServerCodes();
	return (true);
}

bool			RoomManager::notReady()
{
	RtypeProtocol::Data::Code		code;

	code.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::RoomNotReady);
	sentData.str("");
	sentData.write(reinterpret_cast<char *>(&(code.code)), sizeof(code.code));
	if (socket.send(sentData) == false) {
		return (false);
	}
	if (socket.receive(sizeof(RtypeProtocol::Data::RoomInfo)) == false)
		return (false);
	manageServerCodes();
	return (true);
}

// Only call this function once, the first time !
const std::list<Room>				&RoomManager::roomList()
{
	RtypeProtocol::Data::Username	username;
	std::string						_username;
	RtypeProtocol::Data::Room		receivedRoom;

	this->listRooms.clear();
	if (socket.receive(sizeof(RtypeProtocol::Data::Room)) == false) {
		username.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::Username);
		_username = socket.getUsername();
		for (unsigned short i = 0; i < (_username.length() < 12 ? _username.length() : 12); i++)
			username.username[i] = _username.c_str()[i];
		sentData.str("");
		sentData.write(reinterpret_cast<char *>(&(username.code)), sizeof(username.code));
		if (socket.send(sentData) == false) {
			socket.setInternalError(true);
			return (this->listRooms);
		}
		if (!socket.receive(sizeof(RtypeProtocol::Data::RoomBegin))) {
			socket.setInternalError(true);
			return (this->listRooms);
		}
	}
	socket.getReceivedData().read(reinterpret_cast<char *>(&(receivedRoom.code)), sizeof(receivedRoom.code));
	while (receivedRoom.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::Room)) {
		socket.getReceivedData().read(reinterpret_cast<char *>(&(receivedRoom.players)), sizeof(receivedRoom.players));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(receivedRoom.roomID)), sizeof(receivedRoom.roomID));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(receivedRoom.state)), sizeof(receivedRoom.state));
		this->listRooms.push_back(Room(receivedRoom.roomID, receivedRoom.players, receivedRoom.state));
		socket.receive(sizeof(RtypeProtocol::Data::Room));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(receivedRoom.code)), sizeof(receivedRoom.code));
	}
	if (receivedRoom.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomListEnd))
		return (this->listRooms);
	else
		manageServerCodes(receivedRoom.code);
	return (this->listRooms);
}

bool RoomManager::createRoom()
{
	int									biggestRoomId = 0;
	RtypeProtocol::Data::RoomCreation	room;

	for (std::list<Room>::iterator it = listRooms.begin(); it != listRooms.end(); it++) {
		if (it->getId() > biggestRoomId) {
			biggestRoomId = it->getId();
		}
	}
	room.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::RoomCreate);
	room.id = biggestRoomId + 2;
	sentData.str("");
	sentData.write(reinterpret_cast<char *>(&(room.code)), sizeof(room.code));
	sentData.write(reinterpret_cast<char *>(&(room.id)), sizeof(room.id));
	if (!socket.send(sentData)) {
		return (false);
	}
	while (42) {
		if (!socket.receive(sizeof(RtypeProtocol::Data::RoomJoined))) {
			return (false);
		}
		socket.getReceivedData().read(reinterpret_cast<char *>(&(room.code)), sizeof(room.code));
		if (room.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomCreated)) {
			listRooms.push_back(Room(biggestRoomId, 0, RtypeProtocol::roomState::Waiting));
			return (true);
		} else {
			if (manageServerCodes() == false)
				return (false);
		}
	}
	return (true);
}

const std::list<Room> &RoomManager::refreshRoomList()
{
	RtypeProtocol::Data::Code	roomList;
	RtypeProtocol::Data::Room	receivedRoom;

	this->listRooms.clear();
	roomList.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::GameMenu);
	sentData.str("");
	sentData.write(reinterpret_cast<char *>(roomList.code), sizeof(roomList.code));
	if (socket.send(sentData) == false) {
		return (this->listRooms);
	}
	if (!socket.receive(sizeof(RtypeProtocol::Data::RoomBegin))) {
		return (this->listRooms);
	}
	socket.getReceivedData().read(reinterpret_cast<char *>(&(receivedRoom.code)), sizeof(receivedRoom.code));
	while (receivedRoom.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::Room) || receivedRoom.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomList)) {
		socket.getReceivedData().read(reinterpret_cast<char *>(&(receivedRoom.players)), sizeof(receivedRoom.players));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(receivedRoom.roomID)), sizeof(receivedRoom.roomID));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(receivedRoom.state)), sizeof(receivedRoom.state));
		this->listRooms.push_back(Room(receivedRoom.roomID, receivedRoom.players, receivedRoom.state));
		socket.receive(sizeof(RtypeProtocol::Data::Room));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(receivedRoom.code)), sizeof(receivedRoom.code));
	}
	if (receivedRoom.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomListEnd))
		return (this->listRooms);
	else
		manageServerCodes(receivedRoom.code);
	return (this->listRooms);
}

bool RoomManager::joinRoom(const Room &roomToJoin, const bool &spectator)
{
	RtypeProtocol::Data::RoomJoin	roomJoin;
	RtypeProtocol::Data::RoomJoined	joined;

	roomJoin.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::RoomJoin);
	roomJoin.id = roomToJoin.getId();
	roomJoin.mode = spectator ? RtypeProtocol::roomJoinMode::Spectator : RtypeProtocol::roomJoinMode::Player;
	sentData.str("");
	sentData.write(reinterpret_cast<char *>(&(roomJoin.code)), sizeof(roomJoin.code));
	sentData.write(reinterpret_cast<char *>(&(roomJoin.id)), sizeof(roomJoin.id));
	sentData.write(reinterpret_cast<char *>(&(roomJoin.mode)), sizeof(roomJoin.mode));
	if (!socket.send(sentData)) {
		return (false);
	}
	while (42) {
		if (!socket.receive(sizeof(RtypeProtocol::Data::RoomJoined))) {
			return (false);
		}
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.code)), sizeof(joined.code));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.id)), sizeof(joined.id));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.name1)), sizeof(joined.name1));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.name2)), sizeof(joined.name2));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.name3)), sizeof(joined.name3));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.name4)), sizeof(joined.name4));
		if (joined.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomJoined)) {
			currentRoom.setId(joined.id);
			currentRoom.setPlayer1(joined.name1);
			currentRoom.setPlayer2(joined.name2);
			currentRoom.setPlayer3(joined.name3);
			currentRoom.setPlayer4(joined.name4);
			return (true);
		} else if (joined.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrPlayerLimit)) {
			std::cerr << "[Error] Already 4 players in the room." << std::endl;
			return (false);
		} else if (joined.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrAlreadyStarted)) {
			std::cerr << "[Error] Game already started in Room " << roomToJoin.getId() << std::endl;
			return (false);
		} else {
			if (manageServerCodes(joined.code) == false)
				return (false);
		}
	}
	return (true);
}

bool RoomManager::joinRoom(const int &roomToJoin, const bool &spectator)
{
	RtypeProtocol::Data::RoomJoin	roomJoin;
	RtypeProtocol::Data::RoomJoined	joined;

	roomJoin.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::RoomJoin);
	roomJoin.id = roomToJoin;
	roomJoin.mode = spectator ? RtypeProtocol::roomJoinMode::Spectator : RtypeProtocol::roomJoinMode::Player;
	sentData.str("");
	sentData.write(reinterpret_cast<char *>(&(roomJoin.code)), sizeof(roomJoin.code));
	sentData.write(reinterpret_cast<char *>(&(roomJoin.id)), sizeof(roomJoin.id));
	sentData.write(reinterpret_cast<char *>(&(roomJoin.mode)), sizeof(roomJoin.mode));
	if (!socket.send(sentData)) {
		return (false);
	}
	while (42) {
		if (!socket.receive(sizeof(RtypeProtocol::Data::RoomJoined))) {
			return (false);
		}
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.code)), sizeof(joined.code));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.id)), sizeof(joined.id));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.name1)), sizeof(joined.name1));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.name2)), sizeof(joined.name2));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.name3)), sizeof(joined.name3));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.name4)), sizeof(joined.name4));
		if (joined.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomJoined)) {
			currentRoom.setId(joined.id);
			currentRoom.setPlayer1(joined.name1);
			currentRoom.setPlayer2(joined.name2);
			currentRoom.setPlayer3(joined.name3);
			currentRoom.setPlayer4(joined.name4);
			return (true);
		} else if (joined.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrPlayerLimit)) {
			std::cerr << "[Error] Already 4 players in the room." << std::endl;
			return (false);
		} else if (joined.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrAlreadyStarted)) {
			std::cerr << "[Error] Game already started in Room " << roomToJoin << std::endl;
			return (false);
		} else {
			if (manageServerCodes(joined.code) == false)
				return (false);
		}
	}
	return (true);
}

bool								RoomManager::leaveRoom()
{
	RtypeProtocol::Data::Code		leave;
	RtypeProtocol::Data::RoomInfo	room;

	leave.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::RoomLeave);
	sentData.str("");
	sentData.write(reinterpret_cast<char *>(&(leave.code)), sizeof(leave.code));
	if (!socket.send(sentData)) {
		return (false);
	}
	if (!socket.receive(sizeof(RtypeProtocol::Data::RoomInfo)))
		return (false);
	socket.getReceivedData().read(reinterpret_cast<char *>(&(room.code)), sizeof(room.code));
	socket.getReceivedData().read(reinterpret_cast<char *>(&(room.name)), sizeof(room.name));
	if (room.code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomLeft) && std::string(room.name) == socket.getUsername()) {
		return (true);
	} else {
		if (manageServerCodes(room.code) == false) {
			return (false);
		}
	}
	return (true);
}

const std::list<Room>	&RoomManager::getRooms()
{
	return (this->listRooms);
}

void	RoomManager::setCurrentPlayerReadiness(const bool &ready)
{
	if (this->socket.getUsername() == currentRoom.getPlayer1()) {
		this->currentRoom.setP1Ready(ready);
	} else if (this->socket.getUsername() == currentRoom.getPlayer2()) {
		this->currentRoom.setP2Ready(ready);
	} else if (this->socket.getUsername() == currentRoom.getPlayer3()) {
		this->currentRoom.setP3Ready(ready);
	} else if (this->socket.getUsername() == currentRoom.getPlayer4()) {
		this->currentRoom.setP4Ready(ready);
	}
}

bool								RoomManager::manageServerCodes(const int &serverCode)
{
	RtypeProtocol::Data::Code		code;
	RtypeProtocol::Data::Room		receivedRoom;
	RtypeProtocol::Data::RoomInfo	roomInfo;
	RtypeProtocol::Data::RoomBegin	roomBegin;
	RtypeProtocol::Data::RoomJoined	joined;
	RtypeProtocol::Data::GameStart	start;

	if (serverCode == 0)
		socket.getReceivedData().read(reinterpret_cast<char *>(&(code.code)), sizeof(code.code));
	else
		code.code = serverCode;
	switch (RtypeProtocol::convertServer(code.code)) {
	case RtypeProtocol::serverCodes::ErrServerClosing:
		socket.setInternalError(true);
		return (false);
	case RtypeProtocol::serverCodes::Room:
		socket.getReceivedData().read(reinterpret_cast<char *>(&(receivedRoom.players)), sizeof(receivedRoom.players));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(receivedRoom.roomID)), sizeof(receivedRoom.roomID));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(receivedRoom.state)), sizeof(receivedRoom.state));
		listRooms.push_back(Room(receivedRoom.roomID, receivedRoom.players, receivedRoom.state));
		break;
	case RtypeProtocol::serverCodes::RoomLeft:
		socket.getReceivedData().read(reinterpret_cast<char *>(&(roomInfo.name)), sizeof(roomInfo.name));
		if (socket.getUsername() == std::string(roomInfo.name)) {
			currentRoom = Room();
			return (true);
		}
		if (currentRoom.getPlayer1() == std::string(roomInfo.name)) {
			currentRoom.setPlayer1("");
			currentRoom.setNbUsers(currentRoom.getNbUsers() - 1);
		} else if (currentRoom.getPlayer2() == std::string(roomInfo.name)) {
			currentRoom.setPlayer2("");
			currentRoom.setNbUsers(currentRoom.getNbUsers() - 1);
		} else if (currentRoom.getPlayer3() == std::string(roomInfo.name)) {
			currentRoom.setPlayer3("");
			currentRoom.setNbUsers(currentRoom.getNbUsers() - 1);
		} else if (currentRoom.getPlayer4() == std::string(roomInfo.name)) {
			currentRoom.setPlayer4("");
			currentRoom.setNbUsers(currentRoom.getNbUsers() - 1);
		}
		break;
	case RtypeProtocol::serverCodes::RoomList:
		socket.getReceivedData().read(reinterpret_cast<char *>(&(roomBegin.tickrate)), sizeof(roomBegin.tickrate));
		this->tickrate = roomBegin.tickrate;
		this->listRooms.clear();
		break;
	case RtypeProtocol::serverCodes::RoomReady:
		socket.getReceivedData().read(reinterpret_cast<char *>(&(roomInfo.name)), sizeof(roomInfo.name));
		if (currentRoom.getPlayer1() == std::string(roomInfo.name)) {
			currentRoom.setP1Ready(true);
		} else if (currentRoom.getPlayer2() == std::string(roomInfo.name)) {
			currentRoom.setP2Ready(true);
		} else if (currentRoom.getPlayer3() == std::string(roomInfo.name)) {
			currentRoom.setP3Ready(true);
		} else if (currentRoom.getPlayer4() == std::string(roomInfo.name)) {
			currentRoom.setP4Ready(true);
		}
		break;
	case RtypeProtocol::serverCodes::RoomNotReady:
		socket.getReceivedData().read(reinterpret_cast<char *>(&(roomInfo.name)), sizeof(roomInfo.name));
		if (currentRoom.getPlayer1() == std::string(roomInfo.name)) {
			currentRoom.setP1Ready(false);
		} else if (currentRoom.getPlayer2() == std::string(roomInfo.name)) {
			currentRoom.setP2Ready(false);
		} else if (currentRoom.getPlayer3() == std::string(roomInfo.name)) {
			currentRoom.setP3Ready(false);
		} else if (currentRoom.getPlayer4() == std::string(roomInfo.name)) {
			currentRoom.setP4Ready(false);
		}
		break;
	case RtypeProtocol::serverCodes::RoomJoined:
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.id)), sizeof(joined.id));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.name1)), sizeof(joined.name1));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.name2)), sizeof(joined.name2));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.name3)), sizeof(joined.name3));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(joined.name4)), sizeof(joined.name4));
		currentRoom.setId(joined.id);
		currentRoom.setPlayer1(joined.name1);
		currentRoom.setPlayer2(joined.name2);
		currentRoom.setPlayer3(joined.name3);
		currentRoom.setPlayer4(joined.name4);
		if (std::string(joined.name4) == "") {
			if (std::string(joined.name3) == "") {
				if (std::string(joined.name2) == "") {
					currentRoom.setNbUsers(1);
				} else {
					currentRoom.setNbUsers(2);
				}
			} else {
				currentRoom.setNbUsers(3);
			}
		} else {
			currentRoom.setNbUsers(4);
		}
		break;
	case RtypeProtocol::serverCodes::ErrPlayerLimit:
		std::cerr << "[Error] Already 4 players in this room." << std::endl;
		return (false);
	case RtypeProtocol::serverCodes::ErrAlreadyStarted:
		std::cerr << "[Error] Game already started in this room." << std::endl;
		return (false);
	case RtypeProtocol::serverCodes::ErrIDConflict:
		std::cerr << "[Error] This id is already taken by another room. \
Failed to create a new room. You should try to refresh the rooms list and try again." << std::endl;
		return (false);
	case RtypeProtocol::serverCodes::GameStart:
		gameStarted = true;
		socket.getReceivedData().read(reinterpret_cast<char *>(&(start.name1)), sizeof(start.name1));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(start.name2)), sizeof(start.name2));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(start.name3)), sizeof(start.name3));
		socket.getReceivedData().read(reinterpret_cast<char *>(&(start.name4)), sizeof(start.name4));
		currentRoom.setPlayer1(start.name1);
		currentRoom.setPlayer2(start.name2);
		currentRoom.setPlayer3(start.name3);
		currentRoom.setPlayer4(start.name4);
		std::cout << "The game has started with " << currentRoom.getNbUsers() << " players." << std::endl;
		std::cout << "Good luck " << socket.getUsername() << "! :)" << std::endl;
	default:
		return (true);
	}
	return (true);
}

const bool		&RoomManager::getGameStarted() const
{
	return (gameStarted);
}
