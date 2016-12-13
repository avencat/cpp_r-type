#ifndef ROOM_HPP_
# define ROOM_HPP_

# include <vector>
# include <string>

class Room
{
public:
	Room();
	virtual ~Room();

	std::vector<std::string>	roomList();
	bool						createRoom();
	std::vector<std::string>	refreshRoomList();
	bool						joinRoom(std::string &);
	bool						leaveRoom();

private:
	std::string	currentRoom;
};

#endif /* !ROOM_HPP_ */
