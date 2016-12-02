//
// RtypeProtocol.cpp for Rtype in /home/touzet_t/epitech/cpp/rtype/common/inc
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Fri Dec  2 16:56:04 2016 Theo TOUZET
// Last update Fri Dec  2 17:10:52 2016 Theo TOUZET
//

#include "RtypeProtocol.hh"

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
