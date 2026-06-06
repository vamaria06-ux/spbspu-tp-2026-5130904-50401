#include "polygon.hpp"


bool ulanova::operator==(const Point & lhs, const Point & rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool ulanova::operator!=(const Point & lhs, const Point & rhs)
{
  return !(lhs == rhs);
}

bool ulanova::operator==(const Polygon & lhs, const Polygon & rhs)
{
  return lhs.points == rhs.points;
}

bool ulanova::operator!=(const Polygon & lhs, const Polygon & rhs)
{
  return !(lhs == rhs);
}
