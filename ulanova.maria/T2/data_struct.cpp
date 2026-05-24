#include "data_struct.hpp"

#include <string>
#include <istream>
#include <cstdlib>
#include <iomanip>
#include <sstream>


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

std::istream& ulanova::operator>>(std::istream& in, StringIO&& data)
{
  if (!in)
  {
    return in;
  }

  std::string value;
  in >> std::quoted(value);
  if (in)
  {
    data.value = value;
  }
  return in;
}

namespace
{
  bool parseDataStruct(std::istream& in, ulanova::DataStruct& data)
  {
    ulanova::DataStruct input{0.0, 0, ""};
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    using del_t = ulanova::DelimiterIO;
    using input_t = ulanova::DataStructInput;

    in >> del_t{'('};
    in >> del_t{':'} >> input_t{input, hasKey1, hasKey2, hasKey3};
    in >> del_t{':'} >> input_t{input, hasKey1, hasKey2, hasKey3};
    in >> del_t{':'} >> input_t{input, hasKey1, hasKey2, hasKey3};
    in >> del_t{':'} >> del_t{')'};

    if (in && hasKey1 && hasKey2 && hasKey3)
    {
      data = input;
      return true;
    }

    return false;
  }
}

std::istream& ulanova::operator>>(std::istream& in, DataStruct& data)
{
  std::string line;
  while (std::getline(in, line))
  {
    std::istringstream input(line);
    DataStruct parsed{0.0, 0, ""};

    if (parseDataStruct(input, parsed))
    {
      data = parsed;
      return in;
    }
  }

  in.setstate(std::ios_base::failbit);
  return in;
}

std::ostream& ulanova::operator<<(std::ostream& out, const DataStruct& data)
{
  IOGuard guard(out);

  out << "(:key1 ";
  out << std::scientific << std::setprecision(1) << data.key1;
  out << ":key2 " << data.key2 << "ull";
  out << ":key3 " << std::quoted(data.key3);
  out << ":)";

  return out;
}

std::istream& ulanova::operator>>(std::istream& in, DataStructInput&& data)
{
  if (!in)
  {
    return in;
  }

  std::string key;
  in >> key;
  if (!in)
  {
    return in;
  }

  if (key == "key1")
  {
    if (data.hasKey1)
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    in >> DblScientificIO{data.data.key1};
    data.hasKey1 = static_cast< bool >(in);
  }
  else if (key == "key2")
  {
    if (data.hasKey2)
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    in >> UllLiteralIO{data.data.key2};
    data.hasKey2 = static_cast< bool >(in);
  }
  else if (key == "key3")
  {
    if (data.hasKey3)
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    in >> StringIO{data.data.key3};
    data.hasKey3 = static_cast< bool >(in);
  }
  else
  {
    in.setstate(std::ios_base::failbit);
  }

  return in;
}

ulanova::IOGuard::IOGuard(std::basic_ios< char >& stream):
  stream_(stream),
  precision_(stream.precision()),
  width_(stream.width()),
  flags_(stream.flags()),
  fill_(stream.fill())
{}

ulanova::IOGuard::~IOGuard()
{
  stream_.precision(precision_);
  stream_.width(width_);
  stream_.flags(flags_);
  stream_.fill(fill_);
}
