#include <iostream>
#include <vector>
#include <cerrno>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <limits>
#include <thread>
#include "Shape.hpp"

namespace afanasev
{
  bool getArgv(const char * s, long long & out)
  {
    char * end = nullptr;
    errno = 0;
    long long v = std::strtoll(s, &end, 10);

    if (errno == ERANGE || end == s || *end != '\0' || v <= 0)
    {
      return false;
    }
    out = v;
    return true;
  }
}


int main(int argc, char ** argv)
{
  namespace av = afanasev;

  if (argc != 3 && argc != 4)
  {
    std::cerr << "Usage: " << argv[0] << " threads tries [seed]\n";
    return 1;
  }

  long long threads = 0;
  long long tries = 0;
  long long seed = 0;

  if (!av::getArgv(argv[1], threads) || !av::getArgv(argv[2], tries) || (argc == 4 && !av::getArgv(argv[3], seed)))
  {
    std::cerr << "invalid command line argument\n";
    return 1;
  }

  std::vector< av::Shape > shapes;

  long long r = 0;
  long long second = 0;
  long long x = 0;
  long long y = 0;

  while (std::cin >> r)
  {
    if (!(std::cin >> second >> x >> y))
    {
      std::cerr << "invalid figure input\n";
      return 1;
    }

    try
    {
      shapes.emplace_back(r, second, x, y);
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }

  if (!std::cin.eof())
  {
    std::cerr << "invalid figure input\n";
    return 1;
  }

  if (shapes.empty())
  {
    std::cout << std::setprecision(std::numeric_limits< double >::max_digits10);
    std::cout << 0.0 << ' ' << 0.0 << '\n';
    return 0;
  }
  
  double minX = std::numeric_limits< double >::infinity();
  double maxX = -std::numeric_limits< double >::infinity();
  double minY = std::numeric_limits< double >::infinity();
  double maxY = -std::numeric_limits< double >::infinity();

  for (const av::Shape & s : shapes)
  {
    s.extendBBox(minX, maxX, minY, maxY);
  }

  const double bboxArea = (maxX - minX) * (maxY - minY);

  const std::size_t nthreads = static_cast< std::size_t >(threads);

  std::vector< long long > unionCounts(nthreads, 0);
  std::vector< long long > interCounts(nthreads, 0);
  std::vector< std::thread > workers;
  workers.reserve(nthreads);

  const long long base = tries / static_cast< long long >(nthreads);
  const long long rem = tries % static_cast< long long >(nthreads);

  return 0;
}
