#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <vector>

#include "polygon.hpp"

namespace ulanova
{
  using polygons_t = std::vector< ulanova::Polygon >;
  using command_t = void (*)(std::istream &, std::ostream &, const polygons_t &);

  void doCount(std::istream & in, std::ostream & out, const polygons_t & polygons);
}

#endif
