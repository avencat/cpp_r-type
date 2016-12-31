#ifndef PLAYERLINK_HPP_
# define PLAYERLINK_HPP_

# include "Socket.hpp"
# include <sstream>
# include "RtypeProtocol.hh"

class PlayerLink {
private:
        Socket                  &sock;
        std::stringstream       ss;
public:
        PlayerLink (Socket &sock);
        virtual ~PlayerLink ();

        bool    charge();
        bool    shoot();
        bool    move(const int &, const int &);
        bool    leave();
};

#endif /* !PLAYERLINK_HPP_ */
