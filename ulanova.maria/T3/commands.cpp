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
