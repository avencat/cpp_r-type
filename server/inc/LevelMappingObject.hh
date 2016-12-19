//
// LevelMappingObject.hh for RType in /home/touzet_t/epitech/cpp/tests/levelsTEST
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Fri Dec 16 17:07:28 2016 Theo TOUZET
// Last update Fri Dec 16 20:48:05 2016 Theo TOUZET
//

#ifndef LEVELMAPPINGOBJECT_HH_
# define LEVELMAPPINGOBJECT_HH_

# include "LevelMapping.hh"

namespace LevelMapping
{
  class Object: public Relationnals<Object>
  {
  public:
    Object(const mapCode &code = mapCode::None, const Pair &position = Pair(0, 0), const Pair vector = Pair(0, 0),
	   const StringData &name = std::string(""), const StringData &ai = std::string(""));
    ~Object();

  public:
    Object	&operator=(Object const &obj);
    bool	operator==(Object const &obj) const;
    bool	operator<(Object const &obj) const;

  public:
    mapCode	getCode() const;
    void	setCode(const mapCode &_code);
    Pair	getPosition() const;
    void	setPosition(const int &x, const int &y);
    void	setPosition(const Pair &pair);
    Pair	getVector() const;
    void	setVector(const int &x, const int &y);
    void	setVector(const Pair &pair);
    std::string	getName() const;
    StringData	getNameStruct() const;
    void	setName(const std::string &data);
    void	setName(const StringData &data);
    std::string	getAI() const;
    StringData	getAIStruct() const;
    void	setAI(const std::string &data);
    void	setAI(const StringData &data);

  public:
    void	fillObject(const mapCode &_code, const Pair &_position, const Pair &_vector, const std::string &_name, const std::string &_ai);

  private:
    void	setPair(const int &x, const int &y, Pair &pair);
    void	setStringData(const std::string &data, StringData &string);

  private:
    mapCode	code;
    Pair	position;
    Pair	vector;
    StringData	name;
    StringData	ai;
  };

  std::ostream	&operator<<(std::ostream &os, const Object &obj);
  std::ofstream	&operator<<(std::ofstream &ofs, const Object &obj);
  std::fstream	&operator<<(std::fstream &fs, const Object &obj);
  std::istream	&operator>>(std::istream &is, Object &obj);
}

#endif /* !LEVELMAPPINGOBJECT_HH_ */ 
