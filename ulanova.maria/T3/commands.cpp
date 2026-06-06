#include "commands.hpp"

#include <algorithm>
#include <functional>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <numeric>
#include <vector>

namespace
{
  double sumAreas(const std::vector< double > & areas)
  {
    return std::accumulate(areas.begin(), areas.end(), 0.0);
  }

  std::vector< double > getAreas(const std::vector< ulanova::Polygon > & polygons)
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(), ulanova::getArea);

    return areas;
  }

  bool compareVertexCount(const ulanova::Polygon & lhs, const ulanova::Polygon & rhs)
  {
    return lhs.points.size() < rhs.points.size();
  }
}

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

void ulanova::doArea(std::istream & in, std::ostream & out, const polygons_t & polygons)
{
  std::string parameter;
  in >> parameter;

  std::vector< Polygon > selected;

  if (parameter == "EVEN")
  {
    std::copy_if(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(selected),
      hasEvenVertexCount
    );
  }
  else if (parameter == "ODD")
  {
    std::copy_if(
      polygons.begin(),
      polygons.end(),
      std::back_inserter(selected),
      hasOddVertexCount
    );
  }
  else if (parameter == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::logic_error("empty polygon list");
    }

    selected = polygons;
  }
  else
  {
    const size_t count = std::stoul(parameter);

    if (count < 3)
    {
      throw std::logic_error("invalid vertex count");
    }

    using namespace std::placeholders;
    const auto hasCount = std::bind(hasVertexCount, count, _1);

    std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(selected), hasCount);
  }

  std::vector< double > areas(selected.size());
  std::transform(selected.begin(), selected.end(), areas.begin(), getArea);

  double result = sumAreas(areas);

  if (parameter == "MEAN")
  {
    result = result / polygons.size();
  }

  out << std::fixed << std::setprecision(1) << result << '\n';
}

void ulanova::doMax(std::istream & in, std::ostream & out, const polygons_t & polygons)
{
  if (polygons.empty())
  {
    throw std::logic_error("empty polygon list");
  }

  std::string parameter;
  in >> parameter;

  if (parameter == "AREA")
  {
    const std::vector< double > areas = getAreas(polygons);
    const auto maxArea = std::max_element(areas.begin(), areas.end());

    out << std::fixed << std::setprecision(1) << *maxArea << '\n';
  }
  else if (parameter == "VERTEXES")
  {
    const auto maxPolygon = std::max_element(
      polygons.begin(),
      polygons.end(),
      compareVertexCount
    );

    out << maxPolygon->points.size() << '\n';
  }
  else
  {
    throw std::logic_error("invalid MAX parameter");
  }
}

void ulanova::doMin(std::istream & in, std::ostream & out, const polygons_t & polygons)
{
  if (polygons.empty())
  {
    throw std::logic_error("empty polygon list");
  }

  std::string parameter;
  in >> parameter;

  if (parameter == "AREA")
  {
    const std::vector< double > areas = getAreas(polygons);
    const auto minArea = std::min_element(areas.begin(), areas.end());

    out << std::fixed << std::setprecision(1) << *minArea << '\n';
  }
  else if (parameter == "VERTEXES")
  {
    const auto minPolygon = std::min_element(
      polygons.begin(),
      polygons.end(),
      compareVertexCount
    );

    out << minPolygon->points.size() << '\n';
  }
  else
  {
    throw std::logic_error("invalid MIN parameter");
  }
}
