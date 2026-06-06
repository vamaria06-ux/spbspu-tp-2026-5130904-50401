#include "polygon.hpp"

#include <istream>
#include <ostream>

#include "input.hpp"


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

std::istream & ulanova::operator>>(std::istream & in, Point & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  Point temp{0,0};
  in >> DelimiterIO{'('};
  in >> temp.x;
  in >> DelimiterIO{';'};
  in >> temp.y;
  in >> DelimiterIO{')'};

  if (in)
  {
    dest = temp;
  }
  return in;
}

std::ostream & ulanova::operator<<(std::ostream & out, const Point & dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  out << '(' << dest.x << ';' << dest.y << ')';
  return out;
}
