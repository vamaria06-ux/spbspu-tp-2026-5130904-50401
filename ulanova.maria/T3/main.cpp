#include "polygon.hpp"

#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <string>

namespace
{
  using polygons_t = std::vector< ulanova::Polygon >;
  using command_t = void (*)(std::istream &, std::ostream &, const polygons_t &);

  void skipLine(std::istream & in)
  {
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  void doCount(std::istream &, std::ostream &, const polygons_t &)
  {
    throw std::logic_error("COUNT is not implementd");
  }
}

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

  std::vector < ulanova::Polygon > polygons;
  ulanova::readPolygons(input, polygons);

  std::map< std::string, command_t > commands;
  commands["COUNT"] = doCount;

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout, polygons);
    }
    catch(const std::exception &)
    {
      std::cout << "<INVALID COMMAND>\n";
      skipLine(std::cin);
    }
  }

  return 0;
}
