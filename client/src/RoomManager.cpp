#include "RoomManager.hpp"

RoomManager::RoomManager(Socket &socket) : socket(socket)
{
}

RoomManager::~RoomManager()
{
}

// Call this function only the first time you show the RoomListView !!!
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
	return false;
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
	while ((code = reinterpret_cast<RtypeProtocol::Data::Room *>(socket.getReceivedData())->code) == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::Room)) {
		receivedRoom = reinterpret_cast<RtypeProtocol::Data::Room *>(socket.getReceivedData());
		this->listRooms.push_back(Room(receivedRoom->roomID, receivedRoom->players, receivedRoom->state));
		socket.receive(sizeof(RtypeProtocol::Data::Room));
	}
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
	} else if (joined->code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrPlayerLimit)) {
		std::cerr << "[Error] Already 4 players in the room." << std::endl;
		return (false);
	} else {
		std::cerr << "[Error] Game already started in Room " << roomToJoin.getId() << std::endl;
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
	while (42) {
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
	}
	return (true);
}

std::list<Room>	&RoomManager::getRooms()
{
	return (this->listRooms);
}

bool		RoomManager::manageServerCodes()
{
	short	code;

	code = reinterpret_cast<RtypeProtocol::Data::Code *>(socket.getReceivedData())->code;
	if (code == RtypeProtocol::convertShort(RtypeProtocol::serverCodes::ErrServerClosing)) {
		socket.setInternalError(true);
		return (false);
	}
	return (true);
}