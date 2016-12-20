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
