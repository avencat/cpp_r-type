#include "RoomManager.hpp"

RoomManager::RoomManager(Socket &socket) : socket(socket)
{
	listRooms.push_back(Room(1, 2, RtypeProtocol::roomState::Waiting));
	listRooms.push_back(Room(2, 2, RtypeProtocol::roomState::Waiting));
	listRooms.push_back(Room(3, 3, RtypeProtocol::roomState::Playing));
	listRooms.push_back(Room(4, 4, RtypeProtocol::roomState::Full));
}

RoomManager::~RoomManager()
{
}

std::list<Room>	&RoomManager::roomList()
{
	RtypeProtocol::Data::Username	*username;
	std::string						_username;
	int								code;
	RtypeProtocol::Data::Room		*receivedRoom;

	this->listRooms.clear();
	if (socket.receive(sizeof(RtypeProtocol::Data::Room)) == false) {
		username = new RtypeProtocol::Data::Username;
		username->code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::Username);
		_username = socket.getUsername();
		for (short i = 0; i < (_username.length() < 12 ? _username.length() : 12); i++)
			username->username[i] = _username.c_str()[i];
		if (socket.send(username, sizeof(RtypeProtocol::Data::Username)) == false) {
			socket.setInternalError(true);
			delete username;
			return (this->listRooms);
		}
		delete username;
		if (!socket.receive(sizeof(RtypeProtocol::Data::RoomBegin))) {
			socket.setInternalError(true);
			return (this->listRooms);
		}
	}
	while ((code = reinterpret_cast<RtypeProtocol::Data::Room *>(socket.getReceivedData())->code) == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::Room)) {
		receivedRoom = reinterpret_cast<RtypeProtocol::Data::Room *>(socket.getReceivedData());
		this->listRooms.push_back(Room(receivedRoom->roomID, receivedRoom->players, receivedRoom->state));
		socket.receive(sizeof(RtypeProtocol::Data::Room));
	}
	return (this->listRooms);
}

bool RoomManager::createRoom()
{
	int									biggestRoomId = 0;
	RtypeProtocol::Data::RoomCreation	*room;

	for (std::list<Room>::iterator it = listRooms.begin(); it != listRooms.end(); it++) {
		if (it->getId() > biggestRoomId) {
			biggestRoomId = it->getId();
		}
	}
	room = new RtypeProtocol::Data::RoomCreation;
	room->code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::RoomCreate);
	room->id = biggestRoomId + 2;
	if (!socket.send(room, sizeof(RtypeProtocol::Data::RoomCreation))) {
		return (false);
	}
	delete room;
	while (42) {
		if (!socket.receive(sizeof(RtypeProtocol::Data::RoomJoined))) {
			return (false);
		}
		room = reinterpret_cast<RtypeProtocol::Data::RoomCreation *>(socket.getReceivedData());
		if (room->code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomCreated)) {
			listRooms.push_back(Room(biggestRoomId, 0, RtypeProtocol::roomState::Waiting));
			return (true);
		} else {
			if (manageServerCodes() == false)
				return (false);
		}
	}
	return (true);
}

std::list<Room> &RoomManager::refreshRoomList()
{
	RtypeProtocol::Data::Username	*username;
	std::string						_username;
	int								code;
	RtypeProtocol::Data::Room		*receivedRoom;

	this->listRooms.clear();
	if (socket.receive(sizeof(RtypeProtocol::Data::Room)) == false) {
		username = new RtypeProtocol::Data::Username;
		username->code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::Username);
		_username = socket.getUsername();
		for (short i = 0; i < (_username.length() < 12 ? _username.length() : 12); i++)
			username->username[i] = _username.c_str()[i];
		if (socket.send(username, sizeof(RtypeProtocol::Data::Username)) == false) {
			socket.setInternalError(true);
			delete username;
			return (this->listRooms);
		}
		delete username;
		if (!socket.receive(sizeof(RtypeProtocol::Data::RoomBegin))) {
			socket.setInternalError(true);
			return (this->listRooms);
		}
	}
	while ((code = reinterpret_cast<RtypeProtocol::Data::Room *>(socket.getReceivedData())->code) == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::Room) || code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomList)) {
		receivedRoom = reinterpret_cast<RtypeProtocol::Data::Room *>(socket.getReceivedData());
		this->listRooms.push_back(Room(receivedRoom->roomID, receivedRoom->players, receivedRoom->state));
		socket.receive(sizeof(RtypeProtocol::Data::Room));
	}
	manageServerCodes();
	return (this->listRooms);
}

bool RoomManager::joinRoom(const Room &roomToJoin, const bool &spectator)
{
	RtypeProtocol::Data::RoomJoin	*roomJoin;
	RtypeProtocol::Data::RoomJoined	*joined;

	roomJoin = new RtypeProtocol::Data::RoomJoin;
	roomJoin->code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::RoomJoin);
	roomJoin->id = roomToJoin.getId();
	roomJoin->mode = spectator ? RtypeProtocol::roomJoinMode::Spectator : RtypeProtocol::roomJoinMode::Player;
	if (!socket.send(roomJoin, sizeof(roomJoin))) {
		delete roomJoin;
		return (false);
	}
	delete roomJoin;
	while (42) {
		if (!socket.receive(sizeof(RtypeProtocol::Data::RoomJoined))) {
			return (false);
		}
		joined = reinterpret_cast<RtypeProtocol::Data::RoomJoined *>(socket.getReceivedData());
		if (joined->code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomJoined)) {
			currentRoom.setId(joined->id);
			currentRoom.setPlayer1(joined->name1);
			currentRoom.setPlayer2(joined->name2);
			currentRoom.setPlayer3(joined->name3);
			currentRoom.setPlayer4(joined->name4);
			return (true);
		} else if (joined->code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrPlayerLimit)) {
			std::cerr << "[Error] Already 4 players in the room." << std::endl;
			return (false);
		} else if (joined->code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrAlreadyStarted)) {
			std::cerr << "[Error] Game already started in Room " << roomToJoin.getId() << std::endl;
			return (false);
		} else {
			if (manageServerCodes() == false)
				return (false);
		}
	}
	return (true);
}

bool RoomManager::joinRoom(const int &roomToJoin, const bool &spectator)
{
	RtypeProtocol::Data::RoomJoin	*roomJoin;
	RtypeProtocol::Data::RoomJoined	*joined;

	roomJoin = new RtypeProtocol::Data::RoomJoin;
	roomJoin->code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::RoomJoin);
	roomJoin->id = roomToJoin;
	roomJoin->mode = spectator ? RtypeProtocol::roomJoinMode::Spectator : RtypeProtocol::roomJoinMode::Player;
	if (!socket.send(roomJoin, sizeof(roomJoin))) {
		delete roomJoin;
		return (false);
	}
	delete roomJoin;
	while (42) {
		if (!socket.receive(sizeof(RtypeProtocol::Data::RoomJoined))) {
			return (false);
		}
		joined = reinterpret_cast<RtypeProtocol::Data::RoomJoined *>(socket.getReceivedData());
		if (joined->code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomJoined)) {
			currentRoom.setId(joined->id);
			currentRoom.setPlayer1(joined->name1);
			currentRoom.setPlayer2(joined->name2);
			currentRoom.setPlayer3(joined->name3);
			currentRoom.setPlayer4(joined->name4);
			return (true);
		} else if (joined->code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrPlayerLimit)) {
			std::cerr << "[Error] Already 4 players in the room." << std::endl;
			return (false);
		} else if (joined->code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrAlreadyStarted)) {
			std::cerr << "[Error] Game already started in Room " << roomToJoin << std::endl;
			return (false);
		} else {
			if (manageServerCodes() == false)
				return (false);
		}
	}
	return (true);
}

bool								RoomManager::leaveRoom()
{
	RtypeProtocol::Data::Code		*leave;
	RtypeProtocol::Data::RoomInfo	*room;

	leave = new RtypeProtocol::Data::Code;
	leave->code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::RoomLeave);
	if (!socket.send(leave, sizeof(leave))) {
		delete leave;
		return (false);
	}
	delete leave;
	if (!socket.receive(sizeof(RtypeProtocol::Data::RoomInfo)))
		return (false);
	room = reinterpret_cast<RtypeProtocol::Data::RoomInfo *>(socket.getReceivedData());
	if (room->code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomLeft)) {
		return (true);
	} else {
		if (manageServerCodes() == false) {
			return (false);
		}
	}
	return (true);
}

std::list<Room>	&RoomManager::getRooms()
{
	return (this->listRooms);
}

bool								RoomManager::manageServerCodes()
{
	short							code;
	RtypeProtocol::Data::Room		*receivedRoom;
	RtypeProtocol::Data::RoomInfo	*roomInfo;
	RtypeProtocol::Data::RoomBegin	*roomBegin;
	RtypeProtocol::Data::RoomJoined	*joined;

	code = reinterpret_cast<RtypeProtocol::Data::Code *>(socket.getReceivedData())->code;
	if (code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrServerClosing)) {
		socket.setInternalError(true);
		return (false);
	} else if (code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::Room)) {
		receivedRoom = reinterpret_cast<RtypeProtocol::Data::Room *>(socket.getReceivedData());
		listRooms.push_back(Room(receivedRoom->roomID, receivedRoom->players, receivedRoom->state));
	} else if (code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomLeft)) {
		roomInfo = reinterpret_cast<RtypeProtocol::Data::RoomInfo *>(socket.getReceivedData());
		if (socket.getUsername() == roomInfo->name) {
			currentRoom = Room();
			return (true);
		}
		if (currentRoom.getPlayer1() == roomInfo->name) {
			currentRoom.setPlayer1("");
			currentRoom.setNbUsers(currentRoom.getNbUsers() - 1);
		} else if (currentRoom.getPlayer2() == roomInfo->name) {
			currentRoom.setPlayer2("");
			currentRoom.setNbUsers(currentRoom.getNbUsers() - 1);
		} else if (currentRoom.getPlayer3() == roomInfo->name) {
			currentRoom.setPlayer3("");
			currentRoom.setNbUsers(currentRoom.getNbUsers() - 1);
		} else if (currentRoom.getPlayer4() == roomInfo->name) {
			currentRoom.setPlayer4("");
			currentRoom.setNbUsers(currentRoom.getNbUsers() - 1);
		}
	} else if (code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomList)) {
		roomBegin = reinterpret_cast<RtypeProtocol::Data::RoomBegin *>(socket.getReceivedData());
		this->tickrate = roomBegin->tickrate;
	} else if (code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomReady)) {
		roomInfo = reinterpret_cast<RtypeProtocol::Data::RoomInfo *>(socket.getReceivedData());
		if (currentRoom.getPlayer1() == roomInfo->name) {
			currentRoom.setP1Ready(true);
		} else if (currentRoom.getPlayer2() == roomInfo->name) {
			currentRoom.setP2Ready(true);
		} else if (currentRoom.getPlayer3() == roomInfo->name) {
			currentRoom.setP3Ready(true);
		} else if (currentRoom.getPlayer4() == roomInfo->name) {
			currentRoom.setP4Ready(true);
		}
	} else if (code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomNotReady)) {
		roomInfo = reinterpret_cast<RtypeProtocol::Data::RoomInfo *>(socket.getReceivedData());
		if (currentRoom.getPlayer1() == roomInfo->name) {
			currentRoom.setP1Ready(false);
		}
		else if (currentRoom.getPlayer2() == roomInfo->name) {
			currentRoom.setP2Ready(false);
		}
		else if (currentRoom.getPlayer3() == roomInfo->name) {
			currentRoom.setP3Ready(false);
		}
		else if (currentRoom.getPlayer4() == roomInfo->name) {
			currentRoom.setP4Ready(false);
		}
	}
	else if (code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::RoomJoined)) {
		joined = reinterpret_cast<RtypeProtocol::Data::RoomJoined *>(socket.getReceivedData());
		currentRoom.setId(joined->id);
		currentRoom.setPlayer1(joined->name1);
		currentRoom.setPlayer2(joined->name2);
		currentRoom.setPlayer3(joined->name3);
		currentRoom.setPlayer4(joined->name4);
	} else if (code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrPlayerLimit)) {
		std::cerr << "[Error] Already 4 players in this room." << std::endl;
		return (false);
	} else if (code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrAlreadyStarted)) {
		std::cerr << "[Error] Game already started in this room." << std::endl;
		return (false);
	} else if (code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrIDConflict)) {
		std::cerr << "[Error] This id is already taken by another room. \
Failed to create a new room. You should try to refresh the rooms list and try again." << std::endl;
		return (false);
	}
	return (true);
}
