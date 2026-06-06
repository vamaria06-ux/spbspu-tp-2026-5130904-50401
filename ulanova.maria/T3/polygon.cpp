#include "polygon.hpp"

#include <algorithm>
#include <iterator>
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

std::istream & ulanova::operator>>(std::istream & in, Polygon & dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  size_t vertexCount = 0;
  in >> vertexCount;

  if ((!in) || (vertexCount < 3))
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  std::vector< Point > temp;
  temp.reserve(vertexCount);

  using inputIt = std::istream_iterator< Point >;
  std::copy_n(inputIt{in}, vertexCount, std::back_inserter(temp));

  if ((in) && (temp.size() == vertexCount))
  {
    dest.points = temp;
  }
  else
  {
    in.setstate(std::ios_base::failbit);
  }

  return in;
}

std::ostream & ulanova::operator<<(std::ostream & out, const Polygon & dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  out << dest.points.size();

  if (!dest.points.empty())
  {
    out << ' ';
    using outputIt = std::ostream_iterator< Point >;
    std::copy_n(dest.points.begin(), dest.points.size() - 1, outputIt{out," "});
    out << dest.points.back();
  }

  return out;
}
