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
	const std::list<Room>		&roomList();
	bool						createRoom();
	const std::list<Room>		&refreshRoomList();
	bool						joinRoom(const Room &, const bool &spectator);
	bool						joinRoom(const int &, const bool &spectator);
	bool						leaveRoom();
	const std::list<Room>		&getRooms();
	bool						manageServerCodes(const int &code = 0);
	bool						ready();
	bool						notReady();
	const Room					&getCurrentRoom();
	void						setCurrentPlayerReadiness(const bool &ready);

private:
	std::list<Room>		listRooms;
	Room				currentRoom;
	Socket				&socket;
	int					tickrate;
	bool				gameStarted;
	std::stringstream	sentData;
};

#endif /* !ROOMMANAGER_HPP_ */
