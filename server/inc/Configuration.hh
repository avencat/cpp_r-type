//
// Configuration.hh for Spider server in /home/touzet_t/epitech/cpp/cpp_spider/server
//
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
//
// Started on  Thu Nov  3 19:41:48 2016 Theo TOUZET
// Last update Fri Dec 30 17:15:28 2016 Jessica VAN-DEN-ZANDE
//

#ifndef TEST_HH_
# define TEST_HH_

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>

class Configuration
{
public:
  Configuration(const std::string&, const bool _silent = true);
  ~Configuration();

  void	readUpdateConfig();
  void	readUpdateWhitelist();
  void	readUpdateBlacklist();
  void	addToWhitelist(const std::string&);
  void	addToBlacklist(const std::string&);
  void	removeFromWhitelist(const std::string&);
  void	removeFromBlacklist(const std::string&);

  bool		getSilent() const;
  void		setSilent(const bool);
  std::string	getConfigKey(const std::string&) const;
  void		setConfigKey(const std::string&, const std::string&);

  bool	isAuthorizedIP(const std::string&, const unsigned short) const;
  bool	isAuthorizedWhite(const std::string&, const unsigned short) const;
  bool	isAuthorizedBlack(const std::string&, const unsigned short) const;
  void  printConfig();
  void  printWhitelist();
  void  printBlacklist();

private:
  bool					silent;
  std::map<std::string, std::string>	config;
  std::vector<std::string>		whitelist;
  std::vector<std::string>	        blacklist;
};

#endif /* !TEST_HH_ */
