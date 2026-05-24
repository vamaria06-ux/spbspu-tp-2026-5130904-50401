#include "data_struct.hpp"

#include <string>
#include <istream>
#include <cstdlib>
#include <iomanip>


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

std::istream& ulanova::operator>>(std::istream& in, UllLiteralIO&& data)
{
  if (!in)
  {
    return in;
  }
  unsigned long long value = 0;
  in >> value;

  char first = 0;
  char second = 0;
  char third = 0;
  in >> first >> second >> third;

  if(!in)
  {
    return in;
  }

  first = static_cast< char >(std::tolower(first));
  second = static_cast< char >(std::tolower(second));
  third = static_cast< char >(std::tolower(third));

  if ((first != 'u') || (second != 'l') || (third != 'l'))
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  data.value = value;
  return in;
}

std::istream& ulanova::operator>>(std::istream& in, DblScientificIO&& data)
{
  if (!in)
  {
    return in;
  }

  std::string value;
  in >> value;
  if (!in)
  {
    return in;
  }

  const size_t dot = value.find('.');
  const size_t exp = value.find('e');

  if ((dot == std::string::npos) || (exp == std::string::npos))
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  if ((dot == 0) || ( dot + 1 >= exp))
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  if ((exp + 2 > value.size()) || ((value[exp + 1] != '+') && (value[exp + 1] != '-')))
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  char* end = nullptr;
  const double result = std::strtod(value.c_str(), &end);
  if ((end == value.c_str()) || (*end != '\0'))
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  data.value = result;
  return in;
}
