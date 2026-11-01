#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <map>
#include <string>
#include "shape.hpp"
#include <vector>

namespace afanasev
{
  struct Data
  {
    std::map< std::string, Shape > shapes;
    std::map< std::string, std::vector< std::string > > sets;
  };

  bool cmdCircle(std::istream &, std::ostream &, Data &);
  bool cmdSet(std::istream &, std::ostream &, Data &);
  bool cmdShow(std::istream &, std::ostream &, Data &);
  bool cmdShowSet(std::istream &, std::ostream &, Data &);
  bool cmdFrame(std::istream &, std::ostream &, Data &);
  bool cmdFrameSet(std::istream &, std::ostream &, Data &);
  bool cmdSpawn(std::istream &, std::ostream &, Data &);
  bool cmdAreaOn(std::istream &, std::ostream &, Data &);
  bool cmdStatus(std::istream &, std::ostream &, Data &);
  bool cmdWait(std::istream &, std::ostream &, Data &);
}

#endif
