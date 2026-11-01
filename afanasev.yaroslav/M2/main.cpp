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
  afanasev::Data data;
  std::string cmd;

  while (std::cin >> cmd)
  {
    const auto & table = commandTable();
    auto it = table.find(cmd);

    if (it == table.end())
    {
      std::cout << "<UNKNOWN COMMAND>\n";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    if (!it->second(std::cin, std::cout, data))
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  return 0;
}
