#include "commands.hpp"

#include <istream>
#include <ostream>
#include <string>
#include <vector>

namespace afanasev
{
  bool cmdCircle(std::istream & in, std::ostream & out, Data &)
  {
    std::string name;
    long long r, x, y;
    if (!(in >> name >> r >> x >> y))
    {
      return false;
    }
    out << "circle " << name << " " << r << " " << x << " " << y << "\n";
    return true;
  }
}
