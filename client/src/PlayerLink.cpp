#include "PlayerLink.hpp"

PlayerLink::PlayerLink(Socket &_sock) : sock(_sock)
{
}

PlayerLink::~PlayerLink()
{
}

bool                              PlayerLink::charge()
{
        RtypeProtocol::Data::Code       charge;

        ss.str("");
        charge.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::PlayerCharge);
        ss.write(reinterpret_cast<char *>(&(charge.code)), sizeof(charge.code));
        return (sock.send(ss));
}

bool                              PlayerLink::shoot()
{
        RtypeProtocol::Data::Code       shoot;

        ss.str("");
        shoot.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::PlayerShoot);
        ss.write(reinterpret_cast<char *>(&(shoot.code)), sizeof(shoot.code));
        return (sock.send(ss));
}

bool                              PlayerLink::move(const int &x, const int &y)
{
        RtypeProtocol::Data::PlayerMove move;

        ss.str("");
        move.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::PlayerMove);
        move.x = x;
        move.y = y;
        ss.write(reinterpret_cast<char *>(&(move.code)), sizeof(move.code));
        ss.write(reinterpret_cast<char *>(&(move.x)), sizeof(move.x));
        ss.write(reinterpret_cast<char *>(&(move.y)), sizeof(move.y));
        return (sock.send(ss));
}

bool                      PlayerLink::leave()
{
        RtypeProtocol::Data::Code       leave;

        ss.str("");
        leave.code = RtypeProtocol::convertShort(RtypeProtocol::clientCodes::PlayerLeave);
        ss.write(reinterpret_cast<char *>(&(leave.code)), sizeof(leave.code));
        return (sock.send(ss));
}
