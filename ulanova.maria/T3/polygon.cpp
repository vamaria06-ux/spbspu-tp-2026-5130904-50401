#include "polygon.hpp"

#include <cmath>
#include <functional>
#include <numeric>
#include <algorithm>
#include <limits>
#include <iterator>
#include <istream>
#include <ostream>

#include "input.hpp"

namespace
{
  long long getDoubleAreaTerm(const ulanova::Polygon & polygon, size_t index)
  {
    const size_t vertexCount = polygon.points.size();
    const ulanova::Point & current = polygon.points[index];
    const ulanova::Point & next = polygon.points[(index + 1) % vertexCount];

    return (current.x * next.y) - (current.y * next.x);
  }
}

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

void ulanova::readPolygons(std::istream & in, std::vector< Polygon > & dest)
{
  while(!in.eof())
  {
    Polygon polygon{{}};
    in >> polygon;

    if (in)
    {
      dest.push_back(polygon);
    }
    else
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}

double ulanova::getArea(const Polygon & polygon)
{
  if (polygon.points.size() < 3)
  {
    return 0.0;
  }

  const size_t vertexCount = polygon.points.size();

  std::vector< size_t > indexes (vertexCount);
  std::iota(indexes.begin(), indexes.end(), 0);

  std::vector< long long > terms(vertexCount);
  std::transform(
    indexes.begin(),
    indexes.end(),
    terms.begin(),
    std::bind(getDoubleAreaTerm, std::cref(polygon), std::placeholders::_1)
  );

  const long long doubleArea = std::accumulate(terms.begin(), terms.end(), 0ll);

  return std::abs(static_cast< double >(doubleArea)) / 2.0;
}

bool ulanova::hasEvenVertexCount(const Polygon & polygon)
{
  return (polygon.points.size() % 2) == 0;
}

bool ulanova::hasOddVertexCount(const Polygon & polygon)
{
  return (polygon.points.size() % 2 ) != 0;
}

bool ulanova::hasVertexCount(size_t count, const Polygon & polygon)
{
  return polygon.points.size() == count;
}
