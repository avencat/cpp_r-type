#ifndef ROOMMANAGER_HPP_
# define ROOMMANAGER_HPP_

# include <list>
# include <string>
# include <iostream>
# include "Room.hpp"
# include "Socket.hpp"

class RoomManager
{
public:
	RoomManager(Socket &);
	virtual ~RoomManager();

	// Call this function only the first time you show the RoomListView !!!
	std::list<Room>				&roomList();
	bool						createRoom();
	std::list<Room>				&refreshRoomList();
	bool						joinRoom(const Room &, const bool &spectator);
	bool						joinRoom(const int &, const bool &spectator);
	bool						leaveRoom();
	std::list<Room>				&getRooms();
	bool						manageServerCodes();

private:
	std::list<Room>	listRooms;
	Room			currentRoom;
	Socket			&socket;
};

#endif /* !ROOMMANAGER_HPP_ */
