//
// LevelMappingMap.cpp for RType in /home/touzet_t/epitech/cpp/tests/levelsTEST
// 
// Made by Theo TOUZET
// Login   <touzet_t@epitech.net>
// 
// Started on  Fri Dec 16 17:04:54 2016 Theo TOUZET
// Last update Fri Dec 16 21:50:43 2016 Theo TOUZET
//

#include "LevelMappingMap.hh"

LevelMapping::Map::Map()
{
}

LevelMapping::Map::Map(const std::string &name, const bool &forceTrunc) :
  filename(name)
{
  this->open(name, forceTrunc);
}

LevelMapping::Map::~Map()
{
  this->close();
}

bool	LevelMapping::Map::open(const std::string &name, const bool &forceTrunc)
{
  filename = name;
  if (forceTrunc)
      file.open(filename, std::fstream::out | std::fstream::in | std::fstream::trunc);
  else
  {
      file.open(filename, std::fstream::out | std::fstream::in | std::fstream::app);
      if (!file)
          file.open(filename, std::fstream::out | std::fstream::in | std::fstream::trunc);
  }
  return (file.is_open());
}

void	LevelMapping::Map::close()
{
  if (file)
    file.close();
}

bool	LevelMapping::Map::isOpen() const
{
  return (file.is_open());
}

bool    LevelMapping::Map::eof() const
{
    return (file.eof());
}

bool			LevelMapping::Map::dump()
{
  unsigned char		buffer[20];
  long		        addr = 0;
  long			cnt;
  long		    	cnt2;
  long			n;
  std::ios::fmtflags	flags(std::cout.flags());
  std::streampos	ppos = file.tellp();
  std::streampos	gpos = file.tellg();

  if (!file)
    {
      std::cerr << std::endl << "HANDLE - Fatal error!" << std::endl;
      std::cerr << "  Cannot open \"" << filename << "\"" << std::endl;
      return (false);
    }
  std::cout << "Hexdump of \"" << filename << "\":" << std::endl << std::endl;
  std::cout << 
    "Address                Hexadecimal values                      Printable" << std::endl;
  std::cout << 
    "-------  -----------------------------------------------   ----------------" << std::endl;
  file.clear();
  file.seekp(0, std::ios_base::beg);
  file.seekg(0, std::ios_base::beg);
  while (true)
    {
      file.read(reinterpret_cast<char*>(buffer), 16);
      if ((cnt = file.gcount()) <= 0)
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
      if (file.eof())
	break;
    }
  std::cout.flags(flags);
  file.clear();
  file.seekp(ppos);
  file.seekg(gpos);
  return (true);
}

std::streampos  LevelMapping::Map::getStreamPosition()
{
    return (file.tellg() > file.tellp() ? file.tellg() : file.tellp());
}

void	LevelMapping::Map::setStreamPosition(const std::streampos pos)
{
  file.seekp(pos);
  file.seekg(pos);
}

void	LevelMapping::Map::setStreamPosition(const std::streamoff off, const std::ios_base::seekdir way)
{
  file.seekp(off, way);
  file.seekg(off, way);
}

void	LevelMapping::Map::clearStream()
{
  file.clear();
}

void	LevelMapping::Map::writeObject(const LevelMapping::Object &object)
{
  if (file && file.is_open())
    file << object;
}

LevelMapping::Object	&LevelMapping::Map::getNextObject()
{
  file >> obj;
  return (obj);
}

LevelMapping::Object	&LevelMapping::Map::getNextObject(LevelMapping::Object &fillObject)
{
  file >> fillObject;
  return (fillObject);
}
