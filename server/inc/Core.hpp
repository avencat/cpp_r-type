//
// Core.hpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/src
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Thu Dec 29 13:55:10 2016 Maxime BOUCHER
// Last update Sun Jan  1 11:53:21 2017 Maxime BOUCHER
//

#ifndef CORE_HPP_
# define CORE_HPP_

# include "Room.hpp"

class		Core
{
private:
  std::list<Room*>		waiting_rooms;
  std::list<Room*>		active_rooms;

public:
  Core();
  ~Core();

  bool				lockPlayerRoom(const AClient, const bool);
  void				initRooms(int);
  void				checkRooms();
  bool				activateRoom();
  size_t			sizeActivate();
  void				endAll();
  std::list<Room*>		getListRoom();
};

#endif /* !CORE_HPP_ */
