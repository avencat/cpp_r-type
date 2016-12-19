//
// Relationnals.hpp for Relationnals in /home/touzet_t/epitech/cpp/tests/levels
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Tue Dec  6 13:59:40 2016 Theo TOUZET
// Last update Tue Dec  6 14:02:31 2016 Theo TOUZET
//

#ifndef RELATIONNALS_HPP_
# define RELATIONNALS_HPP_

template <class T>
struct Relationnals
{
  friend bool	operator<=(T const &a, T const &b)
  {
    return (a < b || a == b);
  }

  friend bool	operator>(T const &a, T const &b)
  {
    return !(a <= b);
  }

  friend bool	operator!=(T const &a, T const &b)
  {
    return !(a == b);
  }

  friend bool	operator>=(T const &a, T const &b)
  {
    return !(a < b);
  }
};

#endif /* !RELATIONNALS_HPP_ */
