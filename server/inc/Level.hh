//
// Level.hh for rtype in /home/touzet_t/epitech/cpp/tests/levels
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Tue Nov 29 16:27:45 2016 Theo TOUZET
// Last update Tue Nov 29 16:39:49 2016 Theo TOUZET
//

#ifndef LEVEL_HH_
# define LEVEL_HH_

# include <fstream>
# include <string>
# include <vector>
# include "Object.hh"
# include "LevelMappingObject.hh"

class	Level
{
public:
  Level(const std::string &_fileName = "stage1.lvl");
  ~Level();

  const std::string	&getFileName() const;
  void		setFileName(const std::string &fname);
  const std::vector<Object*>   &getObjects() const;
  Object::Type ObjectTypeToType(const LevelMapping::Object::ObjectType &_t) const;

  void    createObject(const LevelMapping::Object &obj);
  int     getAvailableID() const;
  void    deleteObject(const int id);
  void    updateObject();

  bool		readFile();
  bool		readFile(const std::string &fname);
  void      loopGame();

private:
  std::string	        fileName;
  std::ifstream          file;
  int                   timeToWait;
  std::vector<Object*>   objects;
};

#endif /* !LEVEL_HH_ */
