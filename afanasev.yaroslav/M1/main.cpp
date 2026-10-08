#include <iostream>

namespace afanasev
{
  bool getArgv(const char * s, long long & out)
  {
    char * end = nullptr;
    errno = 0;
    long long v = std::strtoll(s, &end, 10);
    if (errno == ERANGE || end == s || *end != '\0')
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
  

  // std::cout << argv[0] << argv[1];

  return 0;
}
