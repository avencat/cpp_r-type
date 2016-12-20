//
// main.cpp for main in /home/van-de_j/Tek3/rendu/RType/rtype/server/src
// 
// Made by Jessica VAN-DEN-ZANDE
// Login   <van-de_j@epitech.net>
// 
// Started on  Mon Dec 19 18:27:07 2016 Jessica VAN-DEN-ZANDE
// Last update Tue Dec 20 13:16:40 2016 Jessica VAN-DEN-ZANDE
//

#include <iostream>
#include <string>
#include "LinuxConnection.hpp"

using namespace std;

int main(int ac, char **av) 
{
  Network	network;
  bool		state;

  if (ac < 3)
    {
      cerr << "./a.out [port] [queue]\n" << endl;
      return -1;
    }
  state = network.initServer(atoi(av[1]), atoi(av[2]));
  network.runServer(state);
  cout << "Server is running." << endl;
  if (state == false)
    {
      cerr << "Error : rv < 0" << endl;
      return -1;
    }
  return 0;
}
