//
// RtypeProtocol.cpp for Rtype in /home/touzet_t/epitech/cpp/rtype/common/inc
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Fri Dec  2 16:56:04 2016 Theo TOUZET
// Last update Tue Dec 20 13:15:33 2016 Jessica VAN-DEN-ZANDE
//

#include "RtypeProtocol.hh"

std::ostream  &RtypeProtocol::operator<<(std::ostream &os, const RtypeProtocol::serverCodes &code)
{
  switch (code)
  {
    case RtypeProtocol::serverCodes::SYN_ACK :
      os << "SYN_ACK";
      break;
    case RtypeProtocol::serverCodes::Pong :
      os << "Pong";
      break;
    case RtypeProtocol::serverCodes::RoomReady :
      os << "RoomReady";
      break;
    case RtypeProtocol::serverCodes::RoomNotReady :
      os << "RoomNotReady";
      break;
    case RtypeProtocol::serverCodes::RoomLeft :
      os << "RoomLeft";
      break;
    case RtypeProtocol::serverCodes::PlayerScore :
      os << "PlayerScore";
      break;
    case RtypeProtocol::serverCodes::PlayerCharge :
      os << "PlayerCharge";
      break;
    case RtypeProtocol::serverCodes::PlayerLeft :
      os << "PlayerLeft";
      break;
    case RtypeProtocol::serverCodes::PlayerLives :
      os << "PlayerLives";
      break;
    case RtypeProtocol::serverCodes::PlayerDead :
      os << "PlayerDead";
      break;
    case RtypeProtocol::serverCodes::GameOver :
      os << "GameOver";
      break;
    case RtypeProtocol::serverCodes::Accepted :
      os << "Accepted";
      break;
    case RtypeProtocol::serverCodes::RoomList :
      os << "RoomList";
      break;
    case RtypeProtocol::serverCodes::Room :
      os << "Room";
      break;
    case RtypeProtocol::serverCodes::RoomListEnd :
      os << "RoomListEnd";
      break;
    case RtypeProtocol::serverCodes::RoomCreated :
      os << "RoomCreated";
      break;
    case RtypeProtocol::serverCodes::RoomJoined :
      os << "RoomJoined";
      break;
    case RtypeProtocol::serverCodes::GameStart :
      os << "GameStart";
      break;
    case RtypeProtocol::serverCodes::ObjectCreate :
      os << "ObjectCreate";
      break;
    case RtypeProtocol::serverCodes::ObjectUpdate :
      os << "ObjectUpdate";
      break;
    case RtypeProtocol::serverCodes::ObjectDestroy :
      os << "ObjectDestroy";
      break;
    case RtypeProtocol::serverCodes::GameScore :
      os << "GameScore";
      break;
    case RtypeProtocol::serverCodes::ErrInvalidName :
      os << "ErrInvalidName";
      break;
    case RtypeProtocol::serverCodes::ErrPlayerLimit :
      os << "ErrPlayerLimit";
      break;
    case RtypeProtocol::serverCodes::ErrAlreadyStarted :
      os << "ErrAlreadyStarted";
      break;
    case RtypeProtocol::serverCodes::ErrIDConflict :
      os << "ErrIDConflict";
      break;
    case RtypeProtocol::serverCodes::ErrServerClosing :
      os << "ErrServerClosing";
      break;
    default:
      os << "None";
      break;
  }
  return (os);
}

std::ostream  &RtypeProtocol::operator<<(std::ostream &os, const RtypeProtocol::clientCodes &code)
{
  switch (code)
  {
    case RtypeProtocol::clientCodes::SYN :
      os << "SYN";
      break;
    case RtypeProtocol::clientCodes::ACK :
      os << "ACK";
      break;
    case RtypeProtocol::clientCodes::Ping :
      os << "Ping";
      break;
    case RtypeProtocol::clientCodes::RoomReady :
      os << "RoomReady";
      break;
    case RtypeProtocol::clientCodes::RoomNotReady :
      os << "RoomNotReady";
      break;
    case RtypeProtocol::clientCodes::PlayerLeave :
      os << "PlayerLeave";
      break;
    case RtypeProtocol::clientCodes::Username :
      os << "Username";
      break;
    case RtypeProtocol::clientCodes::RoomJoin :
      os << "RoomJoin";
      break;
    case RtypeProtocol::clientCodes::RoomCreate :
      os << "RoomCreate";
      break;
    case RtypeProtocol::clientCodes::RoomLeave :
      os << "RoomLeave";
      break;
    case RtypeProtocol::clientCodes::PlayerMove :
      os << "PlayerMove";
      break;
    case RtypeProtocol::clientCodes::PlayerShoot :
      os << "PlayerShoot";
      break;
    case RtypeProtocol::clientCodes::PlayerCharge :
      os << "PlayerCharge";
      break;
    case RtypeProtocol::clientCodes::GameNext :
      os << "GameNext";
      break;
    case RtypeProtocol::clientCodes::GameMenu :
      os << "GameMenu";
      break;
    default:
      os << "None";
      break;
  }
  return (os);
}

short		RtypeProtocol::convertShort(const RtypeProtocol::clientCodes a)
{
  return (static_cast<short>(a));
}

short		RtypeProtocol::convertShort(const RtypeProtocol::serverCodes a)
{
  return (static_cast<short>(a));
}

RtypeProtocol::clientCodes	RtypeProtocol::convertClient(const RtypeProtocol::serverCodes a)
{
  return (static_cast<RtypeProtocol::clientCodes>(a));
}

RtypeProtocol::clientCodes	RtypeProtocol::convertClient(const short a)
{
  return (static_cast<RtypeProtocol::clientCodes>(a));
}

RtypeProtocol::serverCodes	RtypeProtocol::convertServer(const RtypeProtocol::clientCodes a)
{
  return (static_cast<RtypeProtocol::serverCodes>(a));
}

RtypeProtocol::serverCodes	RtypeProtocol::convertServer(const short a)
{
  return (static_cast<RtypeProtocol::serverCodes>(a));
}
