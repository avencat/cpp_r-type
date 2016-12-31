//
// main.cpp for main in /home/van-de_j/Tek3/rendu/RType/rtype/server/src
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Mon Dec 19 18:27:07 2016 Jessica VAN-DEN-ZANDE
// Last update Sat Dec 31 11:19:40 2016 Jessica VAN-DEN-ZANDE
//

#include "LinuxConnection.hpp"

using namespace std;

int		main() 
{
  Network	network;
  Configuration	config("config.ini", false);
  bool		state;

  int port = std::stoi(config.getConfigKey("port"), nullptr, 0);
  state = network.initServer(port);
  network.runServer(state, config);
  if (state == false)
    {
      cerr << "Error : rv < 0" << endl;
      return -1;
    }
  return 0;
}
