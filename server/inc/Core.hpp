//
// Core.hpp for rtype in /home/bouche_2/Tek3/C++/rtype/server/src
// 
// Made by Maxime BOUCHER
// Login   <bouche_2@epitech.net>
// 
// Started on  Thu Dec 29 13:55:10 2016 Maxime BOUCHER
// Last update Sat Dec 31 19:19:32 2016 Maxime BOUCHER
//

#ifndef CORE_HPP_
# define CORE_HPP_

# include "Room.hpp"

class		Core
{
private:
  std::list<Room*>	waiting_rooms;
  std::list<Room*>	active_rooms;

public:
  Core();
  ~Core();

  bool			lockPlayerRoom(const AClient, const bool);
  void			initRooms();
  void			checkRooms();
  bool			activateRoom();
  size_t		sizeActivate();
  void			endAll();
};

#endif /* !CORE_HPP_ */
