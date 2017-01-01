//
// Configuration.cpp for Spider server in /home/touzet_t/epitech/cpp/cpp_spider/server
//
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
//
// Started on  Thu Nov  3 19:40:52 2016 Theo TOUZET
// Last update Sun Jan  1 19:10:44 2017 Jessica VAN-DEN-ZANDE
//

#include "Configuration.hh"

Configuration::Configuration(const std::string &path, const bool _silent) :
  silent(_silent)
{
  config.insert(std::pair<std::string, std::string>("configpath", path));
  config.insert(std::pair<std::string, std::string>("port", "42142"));
  config.insert(std::pair<std::string, std::string>("maxclients", "10"));
  config.insert(std::pair<std::string, std::string>("tickrate", "60"));
  readUpdateConfig();
}

Configuration::~Configuration()
{
}

void		Configuration::readUpdateConfig()
{
  std::ifstream	file;
  std::string	line;
  std::string	tmpKey;
  size_t	f;

  file.open(config["configpath"].c_str(), std::ifstream::in);
  if (!file)
    return;
  while (std::getline(file, line))
    {
      if ((f = line.find("=")) != std::string::npos)
	{
	  tmpKey = line.substr(0, f);
	  std::transform(tmpKey.begin(), tmpKey.end(),
			 tmpKey.begin(), ::tolower);
	  if (!silent)
	    std::cout << "CONFIG: " << tmpKey <<
	      ((config.find(tmpKey) != config.end()) ?
	       " updated to" : " added with") << " value " <<
	      line.substr(f + 1) << std::endl;
	  config.insert(std::pair<std::string, std::string>
			(tmpKey, line.substr(f + 1)));
	}
    }
  file.close();
  readUpdateWhitelist();
  readUpdateBlacklist();
}

void					Configuration::readUpdateWhitelist()
{
  std::ifstream				file;
  std::string				line;
  std::vector<std::string>::iterator	it;

  if (config.find("whitelist") == config.end())
    return;
  file.open(config["whitelist"].c_str(), std::ifstream::in);
  if (!file)
    return;
  while (std::getline(file, line))
    {
      if ((it = std::find(whitelist.begin(), whitelist.end(), line)) ==
	  whitelist.end())
	{
	  if (!silent)
	    std::cout << "WHITELIST: Added " << line << std::endl;
	  whitelist.push_back(line);
	}
    }
  file.close();
}

void					Configuration::readUpdateBlacklist()
{
  std::ifstream				file;
  std::string				line;
  std::vector<std::string>::iterator	it;

  if (config.find("blacklist") == config.end())
    return;
  file.open(config["blacklist"].c_str(), std::ifstream::in);
  if (!file)
    return;
  while (std::getline(file, line))
    {
      if ((it = std::find(blacklist.begin(), blacklist.end(), line)) ==
	  blacklist.end())
	{
	  if (!silent)
	    std::cout << "BLACKLIST: Added " << line << std::endl;
	  blacklist.push_back(line);
	}
    }
  file.close();
}

void	Configuration::addToWhitelist(const std::string &ip)
{
  if (std::find(whitelist.begin(), whitelist.end(), ip) == whitelist.end())
    whitelist.push_back(ip);
}

void	Configuration::addToBlacklist(const std::string &ip)
{
  if (std::find(blacklist.begin(), blacklist.end(), ip) == blacklist.end())
    blacklist.push_back(ip);
}

void	Configuration::removeFromWhitelist(const std::string &ip)
{
  std::vector<std::string>::iterator  it;

  if ((it = std::find(whitelist.begin(), whitelist.end(), ip)) != whitelist.end())
    whitelist.erase(it);
}

void	Configuration::removeFromBlacklist(const std::string &ip)
{
  std::vector<std::string>::iterator  it;

  if ((it = std::find(blacklist.begin(), blacklist.end(), ip)) != blacklist.end())
    blacklist.erase(it);
}

bool	Configuration::getSilent() const
{
  return (silent);
}

void	Configuration::setSilent(const bool _silent)
{
  silent = _silent;
}

std::string	Configuration::getConfigKey(const std::string &key) const
{
  std::string	s;

  if (config.find(key) != config.end())
    {
      s = config.find(key)->second;
      return (s);
    }
  return ("");
}

void	Configuration::setConfigKey(const std::string &key, const std::string &value)
{
  config[key] = value;
}

bool	Configuration::isAuthorizedIP(const std::string &ip, const unsigned short port) const
{
  bool	ret = true;

  if (ret && whitelist.size())
    ret = isAuthorizedWhite(ip, port);
  if (ret && blacklist.size())
    ret = isAuthorizedBlack(ip, port);
  return (ret);
}

bool		Configuration::isAuthorizedWhite(const std::string &ip, const unsigned short port) const
{
  std::string	str(ip);

  
  if (whitelist.size())
    return (true);
  else if (std::find(whitelist.begin(), whitelist.end(), ip) !=
	   whitelist.end())
    {
      if (!silent)
	std::cout << "WHITE IP: " << ip << " is authorized." << std::endl;
      return (true);
    }
  str += ":" + std::to_string(port);
  if (std::find(whitelist.begin(), whitelist.end(), str) != whitelist.end())
    {
      if (!silent)
	std::cout << "WHITE IP: " << ip << " is authorized on port " <<
	  port << "." << std::endl;
      return (true);
    }
  else if (!silent)
    std::cout << "WHITE IP: " << ip << " is not authorized." << std::endl;
  return (false);
}

bool		Configuration::isAuthorizedBlack(const std::string &ip, const unsigned short port) const
{
  std::string	str(ip);

  if (blacklist.size())
    return (true);
  else if (std::find(blacklist.begin(), blacklist.end(), ip) !=
	   blacklist.end())
    {
      if (!silent)
	std::cout << "BLACK IP: " << ip << " is not authorized." << std::endl;
      return (false);
    }
  str += ":" + std::to_string(port);
  if (std::find(blacklist.begin(), blacklist.end(), str) != blacklist.end())
    {
      if (!silent)
	std::cout << "BLACK IP: " << ip << " is not authorized on port " <<
	  port << "." << std::endl;
      return (false);
    }
  else if (!silent)
    std::cout << "BLACK IP: " << ip << " is authorized." << std::endl;
  return (true);
}

void    Configuration::printConfig()
{
  for (std::map<std::string, std::string>::iterator it = config.begin();
       it != config.end(); it++)
    std::cout << it->first << " = " << it->second << std::endl;
}

void    Configuration::printWhitelist()
{
  std::cout << "Whitelist:" << (whitelist.size() ? "" : " none.") << std::endl;
  for (std::vector<std::string>::iterator it = whitelist.begin();
       it != whitelist.end(); it++)
    std::cout << "\t- " << *it << std::endl;
}

void    Configuration::printBlacklist()
{
  std::cout << "Blacklist:" << (blacklist.size() ? "" : " none.") << std::endl;
  for (std::vector<std::string>::iterator it = blacklist.begin();
       it != blacklist.end(); it++)
    std::cout << "\t- " << *it << std::endl;
}
