#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include "commands.hpp"

namespace
{
  using Handler = bool (*)(std::istream &, std::ostream &, afanasev::Data &);

  const std::unordered_map<std::string, Handler> & commandTable()
  {
    static const std::unordered_map<std::string, Handler> t = {
      {"circle",   afanasev::cmdCircle},
      {"set",      afanasev::cmdSet},
      {"show",     afanasev::cmdShow},
      {"showset",  afanasev::cmdShowSet},
      {"frame",    afanasev::cmdFrame},
      {"frameset", afanasev::cmdFrameSet},
      {"spawn",    afanasev::cmdSpawn},
      {"area-on",  afanasev::cmdAreaOn},
      {"status",   afanasev::cmdStatus},
      {"wait",     afanasev::cmdWait},
    };
    return t;
  }
}

int main()
{
  std::cout << "F" << '\n';
}
