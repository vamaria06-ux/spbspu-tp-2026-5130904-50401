#include "polygon.hpp"

#include <iostream>
#include <fstream>

int main(int argc, char ** argv)
{
  if (argc > 2)
  {
    std::cerr << "wrong number of arguments\n";
    return 1;
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "cannot open file\n";
    return 1;
  }

  return 0;
}
