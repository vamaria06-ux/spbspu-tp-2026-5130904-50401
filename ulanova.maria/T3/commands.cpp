#include "commands.hpp"

#include <algorithm>
#include <functional>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>

void ulanova::doCount(std::istream & in, std::ostream & out, const polygons_t & polygons)
{
  std::string parametr;
  in >> parametr;

  if (parametr == "EVEN")
  {
    out << std::count_if(
      polygons.begin(),
      polygons.end(),
      hasEvenVertexCount
    ) << '\n';
  }
  else if (parametr == "ODD")
  {
    out << std::count_if(
      polygons.begin(),
      polygons.end(),
      hasOddVertexCount
    ) << '\n';
  }
  else
  {
    const size_t count = std::stoul(parametr);

    if (count < 3)
    {
      throw std::logic_error("invalid vertex count");
    }

    using namespace std::placeholders;
    const auto hasCount = std::bind(hasVertexCount, count, _1);

    out << std::count_if(polygons.begin(), polygons.end(), hasCount) << '\n';
  }
}
