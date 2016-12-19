//
// LevelMapping.hh for rtype in /home/touzet_t/epitech/cpp/tests/levels
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Tue Nov 29 16:39:34 2016 Theo TOUZET
// Last update Fri Dec 16 21:08:12 2016 Theo TOUZET
//

#ifndef LEVELMAPPING_HH_
# define LEVELMAPPING_HH_

# include <fstream>
# include <iostream>
# include <iomanip>
# include <string>
# include <cmath>
# include "Relationnals.hpp"

namespace LevelMapping
{
  enum class	mapCode: char
  {
    LevelEnd = 0,
    Checkpoint,
    Object,
    MovingObject,
    Wait,
    None
  };

  bool		operator==(const short &a, const mapCode &b);
  bool		operator==(const mapCode &a, const short &b);
  std::ofstream	&operator<<(std::ofstream &ofs, const mapCode &code);
  std::fstream	&operator<<(std::fstream &fs, const mapCode &code);
  std::ostream	&operator<<(std::ostream &os, const mapCode &code);

  struct	Pair: public Relationnals<Pair>
  {
    Pair();
    Pair(int _x, int _y);
    int		x;
    int		y;
    Pair	&operator=(const Pair &p);
    bool	operator==(const Pair &p) const;
    bool	operator<(const Pair &p) const;
  };

  std::ostream	&operator<<(std::ostream &os, const Pair &p);
  std::ofstream	&operator<<(std::ofstream &ofs, const Pair &p);
  std::fstream	&operator<<(std::fstream &fs, const Pair &p);
  std::istream	&operator>>(std::istream &is, Pair &p);

  struct	StringData: public Relationnals<StringData>
  {
    StringData();
    StringData(const std::string &str);
    size_t	length;
    std::string	data;
    StringData	&operator=(const StringData &str);
    StringData	&operator=(const std::string &str);
    bool	operator==(const StringData &str) const;
    bool	operator==(const std::string &str) const;
    bool	operator<(const StringData &str) const;
    bool	operator<(const std::string &str) const;
  };

  std::ofstream	&operator<<(std::ofstream &ofs, const StringData &data);
  std::fstream	&operator<<(std::fstream &fs, const StringData &data);
  std::ostream	&operator<<(std::ostream &os, const StringData &str);
  std::istream	&operator>>(std::istream &is, StringData &data);
}

#endif /* !LEVELMAPPING_HH_ */
