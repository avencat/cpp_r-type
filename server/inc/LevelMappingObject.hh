//
// LevelMappingObject.hh for RType in /home/touzet_t/epitech/cpp/tests/levelsTEST
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Fri Dec 16 17:07:28 2016 Theo TOUZET
// Last update Mon Dec 19 16:37:10 2016 Theo TOUZET
//

#ifndef LEVELMAPPINGOBJECT_HH_
# define LEVELMAPPINGOBJECT_HH_

# include <algorithm>
# include <vector>
# include "LevelMapping.hh"

namespace LevelMapping
{
  class Object: public Relationnals<Object>
  {
  public:
    Object(const mapCode &code = mapCode::None, const std::vector<Sprite> &_sprites = std::vector<Sprite>(),
           const std::vector<Hitbox> &_hitboxes = std::vector<Hitbox>(), const Pair vector = Pair(0, 0), const StringData &ai = std::string(""));
    ~Object();

  public:
    Object	&operator=(Object const &obj);
    bool	operator==(Object const &obj) const;
    bool	operator<(Object const &obj) const;

  public:
    mapCode	getCode() const;
    void	setCode(const mapCode &_code);

    const std::vector<Sprite>	&getSprites() const;
    void	        addSprite(const std::string &name, const int posx, const int posy);
    void	        addSprite(const std::string &name, const Pair &pos);
    void		addSprite(const Sprite &spr);
    void		removeSprite(const std::string &name);
    void		removeSprite(const Pair &pos);
    void		removeSprite(const int x, const int y);
    void		removeSprite(const Sprite &spr);
    void        clearSprites();
    const std::vector<Hitbox>	&getHitboxes() const;
    void	        addHitbox(const int posx, const int posy, const int sizex, const int sizey);
    void	        addHitbox(const Pair &pos, const Pair &size);
    void		addHitbox(const Hitbox &hb);
    void		removeHitbox(const int posx, const int posy, const int sizex, const int sizey);
    void		removeHitbox(const Pair &pos, const Pair &size);
    void		removeHitbox(const Hitbox &hb);
    void        clearHitboxes();
    const Pair	&getVector() const;
    void		setVector(const int x, const int y);
    void		setVector(const Pair &pair);
    std::string	getAI() const;
    const StringData	&getAIStruct() const;
    void		setAI(const std::string &data);
    void		setAI(const StringData &data);

  public:
    void	fillObject(const mapCode &_code, const std::vector<Sprite> &_sprites, const std::vector<Hitbox> &_hitboxes, const Pair &_vector, const std::string &_ai);

  private:
    void	setPair(const int &x, const int &y, Pair &pair);
    void	setStringData(const std::string &data, StringData &string);

  private:
    mapCode		code;
    std::vector<Sprite>	sprites;
    std::vector<Hitbox>	hitboxes;
    Pair		vector;
    StringData		ai;
  };

  std::ostream	&operator<<(std::ostream &os, const Object &obj);
  std::ofstream	&operator<<(std::ofstream &ofs, const Object &obj);
  std::fstream	&operator<<(std::fstream &fs, const Object &obj);
  std::istream	&operator>>(std::istream &is, Object &obj);
}

#endif /* !LEVELMAPPINGOBJECT_HH_ */ 
