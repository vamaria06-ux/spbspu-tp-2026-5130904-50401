#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <cstddef>
#include <iosfwd>
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

  std::istream & operator>>(std::istream & in, Point & dest);
  std::ostream & operator<<(std::ostream & out, const Point & dest);

  std::istream & operator>>(std::istream & in, Polygon & dest);
  std::ostream & operator<<(std::ostream & out, const Polygon & dest);

  void readPolygons(std::istream & in, std::vector< Polygon > & dest);

  double getArea(const Polygon & polygon);

  bool hasEvenVertexCount(const Polygon & polygon);
  bool hasOddVertexCount(const Polygon & polygon);
  bool hasVertexCount(size_t count, const Polygon & polygon);

}

#endif
