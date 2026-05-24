#include "data_struct.hpp"

#include <string>
#include <istream>


bool ulanova::operator<(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3.size() < rhs.key3.size();
}

std::istream& ulanova::operator>>(std::istream& in, DelimiterIO&& data)
{
  if (!in)
  {
    return in;
  }
  char current = 0;
  in >> current;
  if (current != data.expected)
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}

std::istream& ulanova::operator>>(std::istream& in, LabelIO&& data)
{
  if (!in)
  {
    return in;
  }
  std::string current;
  in >> current;
  if (current != data.expected)
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}
