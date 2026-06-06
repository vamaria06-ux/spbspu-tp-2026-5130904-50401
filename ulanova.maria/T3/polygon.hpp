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

  bool operator==(const Point & lhs, const Point & rhs);
  bool operator!=(const Point & lhs, const Point & rhs);

  bool operator==(const Polygon & lhs, const Polygon & rhs);
  bool operator!=(const Polygon & lhs, const Polygon & rhs);

}

#endif
