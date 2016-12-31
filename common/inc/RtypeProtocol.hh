//
// RtypeProtocol.hh for RType in /home/touzet_t/epitech/cpp/rtype/common/inc
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Fri Dec  2 16:33:06 2016 Theo TOUZET
// Last update Fri Dec  2 17:10:23 2016 Theo TOUZET
//

#ifndef RTYPEPROTOCOL_HH_
# define RTYPEPROTOCOL_HH_

# include <iostream>
# include <string>

namespace RtypeProtocol
{
  // Codes
  // Server codes
  enum class serverCodes: short
  {
    SYN_ACK = 100,
    Pong,
    RoomReady,
    RoomNotReady,
    RoomLeft,
    PlayerScore,
    PlayerCharge,
    PlayerLeft,
    PlayerLives,
    PlayerDead,
    GameOver,
    Accepted = 200,
    RoomList,
    Room,
    RoomListEnd,
    RoomCreated,
    RoomJoined,
    GameStart,
    ObjectCreate,
    ObjectUpdate,
    ObjectDestroy,
    GameScore,
    ErrInvalidName = 400,
    ErrPlayerLimit,
    ErrAlreadyStarted,
    ErrIDConflict,
    ErrServerClosing = 500
  };

    std::ostream  &operator<<(std::ostream &os, const serverCodes &code);

  // Client codes
  enum class clientCodes: short
  {
    SYN = 100,
    ACK,
    Ping,
    RoomReady,
    RoomNotReady,
    PlayerLeave,
    Username = 200,
    RoomJoin,
    RoomCreate,
    RoomLeave,
    PlayerMove,
    PlayerShoot,
    PlayerCharge,
    GameNext,
    GameMenu
  };
  // !Codes

  std::ostream  &operator<<(std::ostream &os, const clientCodes &code);

  // Conversion functions
  short		convertShort(const clientCodes a);
  short		convertShort(const serverCodes a);

  clientCodes	convertClient(const serverCodes a);
  clientCodes	convertClient(const short a);

  serverCodes	convertServer(const clientCodes a);
  serverCodes	convertServer(const short a);
  // !Conversion functions

  // Enums
  enum class roomState : char
  {
    Waiting = 0,
    Full,
    Playing
  };

  enum class roomJoinMode : char
  {
    Player = 0,
    Spectator
  };

  enum class gameStatus : char
  {
    Win = 0,
    Lose
  };

  enum class nextStage : char
  {
    NotExist = 0,
    Exist
  };
  // !Enums

  // Structures
  namespace Data {
    struct	Code
    {
      short	code;
    };

    struct	Handshake
    {
      short	code;
      int	syn;
      int	ack;
    };

    struct	Username
    {
      short	code;
      char	username[12];
    };

    struct	RoomBegin
    {
      short	code;
      short	tickrate;
    };

    struct	Room
    {
      short	code;
      int	roomID;
      char	players;
      roomState	state;
    };

    struct		RoomJoin
    {
      short		code;
      int		id;
      roomJoinMode	mode;
    };

    struct	RoomJoined
    {
      short	code;
      int	id;
      char	name1[12];
      char	name2[12];
      char	name3[12];
      char	name4[12];
    };

    struct	RoomCreation
    {
      short	code;
      int	id;
    };

    struct	RoomInfo
    {
      short	code;
      char	name[12];
    };

    struct	GameStart
    {
      short	code;
      char	name1[12];
      char	name2[12];
      char	name3[12];
      char	name4[12];
    };

    struct	PlayerMove
    {
      short	code;
      char	x;
      char	y;
    };

    struct	PlayerCharge
    {
      short	code;
      char	charge1;
      char	charge2;
      char	charge3;
      char	charge4;
    };

    struct	ObjectCreate
    {
      short	code;
      short	id;
      int	posX;
      int	posY;
      int	vecX;
      int	vecY;
      long	name;
    };

    struct	ObjectUpdate
    {
      short	code;
      short	id;
      int	posX;
      int	posY;
    };

    struct	ObjectDestroy
    {
      short	code;
      short	id;
    };

    struct	PlayerScore
    {
      short	code;
      long	score;
    };

    struct	PlayerInfo
    {
      short	code;
      char	info;
    };

    struct		GameOver
    {
      short		code;
      gameStatus	status;
    };

    struct	GameScore
    {
      short	code;
      long	score1;
      long	score2;
      long	score3;
      long	score4;
      long	highest;
      nextStage	next;
    };

    struct	GameHighest
    {
      short	code;
      long	score;
      char	name[12];
    };
    // !Structures
  }
}

#endif /* !RTYPEPROTOCOL_HH_ */
