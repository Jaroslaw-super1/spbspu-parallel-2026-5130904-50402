#include "commands.hpp"

#include <istream>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>

namespace afanasev
{
  namespace
  {
    bool isValidName(const std::string & s)
    {
      if (s.empty()) return false;
      const char c = s.front();
      return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    void printShape(std::ostream & out, const Shape & sh)
    {
      out << sh.radius() << " " << sh.center() << "\n";
    }
  }

  bool cmdCircle(std::istream & in, std::ostream &, Data & data)
  {
    std::string name;
    long long r, x, y;
    if (!(in >> name >> r >> x >> y) || r <= 0 || !isValidName(name) || data.shapes.count(name) > 0)
    {
      return false;
    }

    data.shapes.emplace(name, Shape::makeCircle(r, x, y));
    return true;
  }

  bool cmdSet(std::istream & in, std::ostream &, Data & data)
  {
    std::string name;
    long long n;

    if (!(in >> name >> n) || (n < 0) || (!isValidName(name)) || (data.sets.count(name) > 0))
    {
      return false;
    }

    std::vector< std::string > names;
    names.reserve(static_cast< std::size_t >(n));
    for (long long i = 0; i < n; ++i)
    {
      std::string s;
      if (!(in >> s) || (data.shapes.count(s) == 0))
      {
        return false;
      }
      names.push_back(s);
    }

    data.sets.emplace(name, std::move(names));
    return true;
  }

  bool cmdShow(std::istream & in, std::ostream & out, Data & data)
  {
    std::string name;
    if (!(in >> name))
    {
      return false;
    }

    auto it = data.shapes.find(name);
    if (it == data.shapes.end())
    {
      return false;
    }

    printShape(out, it->second);
    return true;
  }

  bool cmdShowSet(std::istream & in, std::ostream & out, Data & data)
  {
    std::string name;
    if (!(in >> name))
    {
      return false;
    }

    auto it = data.sets.find(name);
    if (it == data.sets.end())
    {
      return false;
    }

    for (const auto & shapeName : it->second)
    {
      auto sit = data.shapes.find(shapeName);
      if (sit == data.shapes.end())
      {
        return false;
      }
      printShape(out, sit->second);
    }
    return true;
  }

  bool cmdFrame(std::istream & in, std::ostream & out, Data & data)
  {
    std::string name;
    if (!(in >> name))
    {
      return false;
    }

    auto it = data.shapes.find(name);
    if (it == data.shapes.end())
    {
      return false;
    }

    const bbox_t b = it->second.bbox();
    out << "(" << b.min_x << " " << b.min_y << ") (" << b.max_x << " " << b.max_y << ")\n";
    return true;
  }

  bool cmdFrameSet(std::istream & in, std::ostream & out, Data & data)
  {
    std::string name;
    if (!(in >> name))
    {
      return false;
    }

    auto it = data.sets.find(name);
    if (it == data.sets.end())
    {
      return false;
    }

    const std::vector< std::string > & names = it->second;
    if (names.empty())
    {
      return false;
    }

    bbox_t result{};
    bool first = true;
    for (const auto & shapeName : names)
    {
      auto sit = data.shapes.find(shapeName);
      if (sit == data.shapes.end())
      {
        return false;
      }
      const bbox_t b = sit->second.bbox();
      if (first)
      {
        result = b;
        first = false;
      }
      else
      {
        result.min_x = std::min(result.min_x, b.min_x);
        result.min_y = std::min(result.min_y, b.min_y);
        result.max_x = std::max(result.max_x, b.max_x);
        result.max_y = std::max(result.max_y, b.max_y);
      }
    }

    out << "(" << result.min_x << " " << result.min_y << ") (" << result.max_x << " " << result.max_y << ")\n";
    return true;
  }

  bool cmdSpawn(std::istream & in, std::ostream & out, Data &)
  {
    std::string name;
    long long seed;

    if (!(in >> name >> seed) || seed < 0)
    {
      return false;
    }
    out << "spawn " << name << " " << seed << "\n";
    return true;
  }

  bool cmdAreaOn(std::istream & in, std::ostream & out, Data &)
  {
    std::string proc, calc, set;
    long long threads, tries;
    if (!(in >> proc >> calc >> set >> threads >> tries))
    {
      return false;
    }
    if (threads <= 0 || tries <= 0)
    {
      return false;
    }
    out << "area-on " << proc << " " << calc << " " << set
        << " " << threads << " " << tries << "\n";
    return true;
  }

  bool cmdStatus(std::istream & in, std::ostream & out, Data &)
  {
    std::string name;
    if (!(in >> name))
    {
      return false;
    }
    out << "status " << name << "\n";
    return true;
  }

  bool cmdWait(std::istream & in, std::ostream & out, Data &)
  {
    std::string name;
    if (!(in >> name))
    {
      return false;
    }
    out << "wait " << name << "\n";
    return true;
  }
}
