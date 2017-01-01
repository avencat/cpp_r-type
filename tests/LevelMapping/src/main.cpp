#include <chrono>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include "LevelMapping.hh"
#include "LevelMappingMap.hh"
#include "Level.hh"

bool		serializeData(const std::string &fname, const LevelMapping::Object &obj, const bool trunc = false)
{
  std::ofstream	f(fname, (trunc ? std::ios_base::trunc : std::ios_base::app));

  if (f.is_open())
    {
      f << obj;
      f.close();
    }
  else
    {
      std::cerr << "Failed to write file.." << std::endl;
      return (true);
    }
  return (false);
}

bool	unserializeData(const std::string &fname, LevelMapping::Object &obj)
{
  std::ifstream	f(fname);

  obj = LevelMapping::Object();
  if (f.is_open())
    {
      f >> obj;
      f.close();
    }
  else
    return (true);
  return (false);
}

bool	unserializeData(std::ifstream &f, LevelMapping::Object &obj)
{
  obj = LevelMapping::Object();
  if (f.is_open())
    f >> obj;
  else
    return (true);
  return (false);
}

void			dumpFile(std::ifstream &f, const std::string &fname)
{
  long int		addr = 0;
  unsigned char		buffer[20];
  long int		cnt;
  long int		cnt2;
  long			n;
  std::ios::fmtflags	flags(std::cout.flags());

  if (!f) 
    {
      std::cerr << std::endl << "HANDLE - Fatal error!" << std::endl;
      std::cerr << "  Cannot open \"" << fname << "\"" << std::endl;
      return;
    }
  std::cout << "Hexdump of \"" << fname << "\":" << std::endl << std::endl;
  std::cout << 
    "Address                Hexadecimal values                      Printable" << std::endl;
  std::cout << 
    "-------  -----------------------------------------------   ----------------" << std::endl;
  while (true)
    {
      f.read(reinterpret_cast<char*>(buffer), 16);
      if ((cnt = f.gcount()) <= 0)
	break;
      std::cout << std::setw(7) << static_cast<int>(addr) << "  ";
      addr += 16;
      for (cnt2 = 0, n = 0; n < 16; ++n)
	{   
	  if (++cnt2 <= cnt)
	    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[n]) << ' ';
	  else
	    std::cout << "   ";
	}
      std::cout << std::setfill (' ') << " |";
      for (cnt2 = 0, n = 0; n < 16; ++n)
	{
	  if (++cnt2 <= cnt)
	    {
	      if (buffer[n] < 32 || 126 < buffer[n])
		std::cout << '.';
	      else
		std::cout << buffer[n];
	    }
	}
      std::cout << "|" << std::endl << std::dec;
      if (f.eof())
	break;
    }
  f.close();
  std::cout.flags(flags);
}

void			dumpFile(const std::string &fname)
{
  std::ifstream		f;

  f.open(fname);
  dumpFile(f, fname);
}

int	testLevelMapping(const bool &hasFailed, const std::string &testName)
{
  if (hasFailed)
    {
      std::cerr << "===" << testName << " test FAILED===" << std::endl << std::endl;
      return (1);
    }
  std::cout << "===" << testName << " test SUCCESS===" << std::endl << std::endl;
  return (0);
}

bool    simpleObject(const std::string &fname)
{
  LevelMapping::Object	a;
  LevelMapping::Object	b;
  std::ofstream		f(fname);

  std::cout << "==BASIC OBJECT TO FILE==" << std::endl;
  a.setCode(LevelMapping::mapCode::Object);
  a.addSprite(LevelMapping::Sprite(std::string("name"), LevelMapping::Pair(20, 50)));
  a.setAI("ai.dll");
  std::cout << "---Struct to output---" << std::endl << a << std::endl;
  if (serializeData(fname, a, true))
    return (true);
  dumpFile(fname);
  if (unserializeData(fname, b))
    return (true);
  std::cout << std::endl;
  std::cout << "b:" << std::endl << b << std::endl;
  return (false);
}

bool						multipleObjects(const std::string &fname)
{
  std::vector<LevelMapping::Sprite> sprs1;
  std::vector<LevelMapping::Sprite> sprs2;

  sprs1.push_back(LevelMapping::Sprite(std::string("name a"), LevelMapping::Pair(200, 150)));
  sprs2.push_back(LevelMapping::Sprite(std::string("name a"), LevelMapping::Pair(15, 25)));
  LevelMapping::Object	a(LevelMapping::mapCode::Object, LevelMapping::Object::ObjectType::ENEMY, sprs1);
  LevelMapping::Object	b(LevelMapping::mapCode::Object, LevelMapping::Object::ObjectType::PLAYER, sprs2, std::vector<LevelMapping::Hitbox>());
  LevelMapping::Object	c(LevelMapping::mapCode::MovingObject, LevelMapping::Object::ObjectType::OBSTACLE, sprs2, std::vector<LevelMapping::Hitbox>(), LevelMapping::Pair(42, 0));
  LevelMapping::Object	d(LevelMapping::mapCode::Checkpoint);
  LevelMapping::Object	e(LevelMapping::mapCode::Wait);
  e.setWaitTime(5000);
  LevelMapping::Object	unser;
  std::vector<LevelMapping::Object>		objects;
  std::vector<LevelMapping::Object>::iterator	it;
  LevelMapping::Map	map(fname);
  size_t		i = 0;

  std::cout << "==MULTIPLE OBJECTS TO FILE==" << std::endl;
  std::cout << "---Structs to output---" << std::endl << "a:" << std::endl << a << std::endl;
  std::cout << "b:" << std::endl << b << std::endl;
  std::cout << "c:" << std::endl << c << std::endl;
  std::cout << "d:" << std::endl << d << std::endl;
  std::cout << "e:" << std::endl << e << std::endl;
  if (serializeData(fname, a, true) || serializeData(fname, b) || serializeData(fname, c) || serializeData(fname, d) || serializeData(fname, e))
    return (true);
  std::cout << "Is open? " << std::boolalpha << map.isOpen() << std::endl;
  map.dump();
  objects.push_back(a);
  objects.push_back(b);
  objects.push_back(c);
  objects.push_back(d);
  objects.push_back(e);
  it = objects.begin();
  std::cout << std::endl << "--Unserialized data structs--" << std::endl;
  while ((unser = map.getNextObject()).getCode() != LevelMapping::mapCode::LevelEnd)
    {
      std::cout << std::endl << "Unserialized data set " << ++i << ":" << std::endl << unser << std::endl;
      if (it != objects.end() && *it != unser)
	{
	  std::cerr << "Failed while comparing structures:" << std::endl <<
	    "Unserialized:" << std::endl << unser << std::endl <<
	    "*IT:" << std::endl << *it << std::endl;
	  return (true);
	}
      ++it;
    }
  if (it != objects.end())
    return (true);
  return (false);
}

bool			tonOfObjects(const std::string &fname)
{
  std::vector<LevelMapping::Sprite> sprs;
  std::vector<LevelMapping::Hitbox> hbxs;

  sprs.push_back(LevelMapping::Sprite(std::string("ton of duplicate"), LevelMapping::Pair(500, 10)));
  hbxs.push_back(LevelMapping::Hitbox(LevelMapping::Pair(0, 0), LevelMapping::Pair(200, 20)));
  LevelMapping::Object	a(LevelMapping::mapCode::Object, LevelMapping::Object::ObjectType::ENEMY, sprs, hbxs);
  LevelMapping::Object	unser;
  size_t		x = 0;

  std::cout << "==TON OF OBJECTS TO FILE==" << std::endl;
  std::cout << "---Struct to output---" << std::endl << "struct:" << std::endl << a << std::endl;
  for (size_t i = 0; i < 5000; ++i)
    if (serializeData(fname, a, (!i ? true : false)))
      return (true);
  LevelMapping::Map	map(fname);
  map.dump();
  while (map.getNextObject(unser).getCode() != LevelMapping::mapCode::LevelEnd)
    {
      if (unser != a)
	return (true);
      ++x;
    }
  if (x != 5000)
    return (true);
  std::cout << "---Unserialized struct is the same than struct to output---" << std::endl;
  return (false);
}


bool		        objectsToMap(const std::string &fname)
{
  std::vector<LevelMapping::Sprite> sprs1 = std::vector<LevelMapping::Sprite>{LevelMapping::Sprite(std::string("Write this in a map!"), LevelMapping::Pair(100, 150))};
  std::vector<LevelMapping::Sprite> sprs2 = std::vector<LevelMapping::Sprite>{LevelMapping::Sprite(std::string("This too!"), LevelMapping::Pair(10, 50))};
  std::vector<LevelMapping::Hitbox> hbs = std::vector<LevelMapping::Hitbox>{LevelMapping::Hitbox(LevelMapping::Pair(10, 50), LevelMapping::Pair(25, 10))};

  LevelMapping::Object	a(LevelMapping::mapCode::Object, LevelMapping::Object::ObjectType::PLAYER, sprs1);
  LevelMapping::Object	b(LevelMapping::mapCode::Object, LevelMapping::Object::ObjectType::PLAYERBULLET, sprs2, hbs);
  LevelMapping::Object	unser;
  size_t		x = 0;
  LevelMapping::Map	map(fname, true);

  std::cout << "==OBJECT TO MAP==" << std::endl;
  std::cout << "---Struct to output---" << std::endl << "struct a:" << std::endl << a << std::endl << "struct b:" << std::endl << b << std::endl;
  map.writeObject(a);
  map.writeObject(b);
  map.dump();
  map.clearStream();
  map.setStreamPosition(0, std::ios_base::beg);
  while (map.getNextObject(unser).getCode() != LevelMapping::mapCode::LevelEnd)
    {
      std::cout << "Unserialized data:" << std::endl << unser << std::endl;
      if (unser != a && unser != b)
    	return (true);
      ++x;
    }
  if (x != 2)
    return (true);
  std::cout << "---Unserialized struct are the same than struct to output---" << std::endl;
  return (false);
}

bool    levelMappingObjectToObject()
{
    std::vector<LevelMapping::Sprite> sprs = std::vector<LevelMapping::Sprite>{LevelMapping::Sprite(std::string("01"), LevelMapping::Pair(100, 150))};
    std::vector<LevelMapping::Hitbox> hbs = std::vector<LevelMapping::Hitbox>{LevelMapping::Hitbox(LevelMapping::Pair(10, 50), LevelMapping::Pair(25, 10))};
    LevelMapping::Object    a(LevelMapping::mapCode::Object, LevelMapping::Object::ObjectType::PLAYER, sprs, hbs);

    std::cout << "==LEVEL MAPPING OBJECT TO OBJECT==" << std::endl;
    std::cout << "---LevelMapping Object---" << std::endl << "Struct:" << std::endl << a << std::endl;
    Level   l("", true);
    l.createObject(a);
    const std::vector<Object*> objs = l.getObjects();
    std::cout << *(objs[0]) << std::endl;
    if (objs[0]->getType() == Object::Type::PLAYER && objs[0]->getComponents().size() == 2)
    {
        std::cout << "---Object data does match LevelMappingObject data---" << std::endl;
        return (false);
    }
    std::cerr << "---Object data does not match LevelMappingObject data---" << std::endl;
    return (true);
}

bool    levelMappingMapRead(const std::string &fname)
{
    std::vector<LevelMapping::Sprite> sprs = std::vector<LevelMapping::Sprite>{LevelMapping::Sprite(std::string("01"), LevelMapping::Pair(100, 150))};
    std::vector<LevelMapping::Hitbox> hbs = std::vector<LevelMapping::Hitbox>{LevelMapping::Hitbox(LevelMapping::Pair(10, 50), LevelMapping::Pair(25, 10))};
    LevelMapping::Object    a(LevelMapping::mapCode::Object, LevelMapping::Object::ObjectType::PLAYER, sprs, hbs);
    LevelMapping::Object    b(LevelMapping::mapCode::Wait);
    LevelMapping::Map       map(fname);
    int                     waitTime = 2500;
    Level   l(fname, true);
    std::vector<Object*>    objs;
    std::chrono::steady_clock::time_point   waitingSince;
    std::chrono::steady_clock::time_point   tp;
    std::chrono::duration<double>           time_span;
    bool    hasWait = false;

    b.setWaitTime(waitTime);
    std::cout << "==LEVEL MAPPING OBJECT TO OBJECT==" << std::endl;
    std::cout << "---LevelMapping Object---" << std::endl << "Struct:" << std::endl << a << std::endl;
    map.writeObject(a);
    map.writeObject(b);
    map.writeObject(a);
    map.dump();
    std::cout << std::endl << "Program should be \"paused\" for " << static_cast<double>(b.getWaitTime()) / 1000 << " seconds." << std::endl;
    waitingSince = std::chrono::steady_clock::now();
    while (l.readFile())
    {
        if (!hasWait && !l.isWaitOver())
        {
            hasWait = true;
            std::cout << "Is waiting.. dumping current Level:" << std::endl;
            l.dump();
        }
    }
    tp = std::chrono::steady_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(tp - waitingSince);
    if (time_span.count() < static_cast<double>(waitTime) / 1000)
    {
        std::cerr << "---Failure: Program did not wait for " << static_cast<double>(b.getWaitTime()) / 1000 <<
            " seconds (only " << time_span.count() << " seconds)---" << std::endl;
        return (true);
    }
    std::cout << "\"Paused\" for " << time_span.count() << " seconds." << std::endl << std::endl;
    objs = l.getObjects();
    if (objs.size() != 2)
    {
        std::cerr << "---Failure: Level has " << objs.size() << " objects where expecting 2 only---" << std::endl;
        return (true);
    }
    l.dump();
    return (false);
}

bool        readLevelRealMap(const std::string &fname)
{
    Level   l(fname);
    std::chrono::steady_clock::time_point   first = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point   middle;
    std::chrono::steady_clock::time_point   last;
    std::chrono::duration<double>           time_span;

    std::cout << "==Real read test on level \"" << fname << "\"==" << std::endl;
    while (l.readFile());
    middle = std::chrono::steady_clock::now();
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(middle - first);
    l.dump();
    last = std::chrono::steady_clock::now();
    std::cout << std::endl << "Took " << time_span.count() << " seconds to read level content from file." << std::endl;
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(last - middle);
    std::cout << "Took " << time_span.count() << " seconds to dump level content." << std::endl;
    time_span = std::chrono::duration_cast<std::chrono::duration<double>>(last - first);
    std::cout << "Total time taken: " << time_span.count() << " seconds." << std::endl;
    return (false);
}

int		main()
{
  size_t	errNbr = 0;

  errNbr += testLevelMapping(simpleObject("testSimpleObject.lvl"), "Simple object");
  errNbr += testLevelMapping(multipleObjects("testMultipleObjects.lvl"), "Multiple objects");
  errNbr += testLevelMapping(tonOfObjects("testTonOfObjects.lvl"), "Lot of objects");
  errNbr += testLevelMapping(objectsToMap("testObjectsToMap.lvl"), "Objects to map");
  errNbr += testLevelMapping(levelMappingObjectToObject(), "Level Mapping Object to Object");
  errNbr += testLevelMapping(levelMappingMapRead("testObjectsRead.lvl"), "Level Mapping Map read");
  errNbr += testLevelMapping(readLevelRealMap("testObjectsToMap.lvl"), "Level read test for objects to map");
  std::cout << std::endl << "===FINAL RESULT===" << std::endl;
  std::cout << errNbr << " error" << (errNbr > 1 ? "s" : "") << " detected." << std::endl;
  std::cout << "===END OF RESULT===" << std::endl;
  return (0);
}
