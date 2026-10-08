#include <iostream>

namespace afanasev
{
}


int main(int argc, char ** argv)
{
  if (argc != 3 && argc != 4)
  {
    std::cerr << "Usage: " << argv[0] << " threads tries [seed]\n";
    return 1;
  }

  // std::cout << argv[0] << argv[1];

  return 0;
}
