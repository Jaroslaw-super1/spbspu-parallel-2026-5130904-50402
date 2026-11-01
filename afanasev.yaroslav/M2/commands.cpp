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

  bool cmdSet(std::istream & in, std::ostream & out, Data &)
  {
    std::string name;
    long long n;
    if (!(in >> name >> n) || n < 0)
    {
      return false;
    }

    std::vector< std::string > names;
    names.reserve(static_cast< std::size_t >(n));
    for (long long i = 0; i < n; ++i)
    {
      std::string s;
      if (!(in >> s))
      {
        return false;
      }
      names.push_back(s);
    }

    out << "set " << name << " " << n;
    for (const auto & s : names)
    {
      out << " " << s;
    }
    out << "\n";
    return true;
  }

  bool cmdShow(std::istream & in, std::ostream & out, Data &)
  {
    std::string name;
    if (!(in >> name))
    {
      return false;
    }
    out << "show " << name << "\n";
    return true;
  }

  bool cmdShowSet(std::istream & in, std::ostream & out, Data &)
  {
    std::string name;
    if (!(in >> name))
    {
      return false;
    }
    out << "showset " << name << "\n";
    return true;
  }
}
