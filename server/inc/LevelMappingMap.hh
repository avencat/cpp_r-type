//
// LevelMappingMap.hh for RType in /home/touzet_t/epitech/cpp/tests/levelsTEST
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Fri Dec 16 17:02:41 2016 Theo TOUZET
// Last update Fri Dec 16 21:26:42 2016 Theo TOUZET
//

#ifndef LEVELMAPPINGMAP_HH_
# define LEVELMAPPINGMAP_HH_

# include "LevelMappingObject.hh"

namespace LevelMapping
{
  class	Map
  {
  public:
    Map();
    Map(const std::string &name);
    ~Map();

  public:
    bool	open(const std::string &name);
    void    close();
    bool	isOpen() const;
    bool    eof() const;

  public:
    bool	dump();

    std::streampos  getStreamPosition();
    void    setStreamPosition(const std::streampos pos);
    void	setStreamPosition(const std::streamoff off, const std::ios_base::seekdir way);
    void	clearStream();

    void	writeObject(const Object &object);
    Object	&getNextObject();
    Object	&getNextObject(Object &fillObject);

  private:
    std::string		filename;
    std::fstream	file;
    Object		obj;
  };
}

#endif /* !LEVELMAPPINGMAP_HH_ */
