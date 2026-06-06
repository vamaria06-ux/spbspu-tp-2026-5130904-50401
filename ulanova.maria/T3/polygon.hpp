#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>

namespace ulanova
{
  struct Point
  {
    int x;
    int y;
  };

  struct Polygon
  {
    std::vector < Point > points;
  };

}

#endif
