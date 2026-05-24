#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iosfwd>
#include <string>

namespace ulanova
{
  struct DataStruct
  {
    double key1;
    unsigned long long key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char expected;
  };

  struct LabelIO
  {
    std::string expected;
  };

  struct UllLiteralIO
  {
    unsigned long long& value;
  };

  struct DblScientificIO
  {
    double& value;
  };

  struct StringIO
  {
    std::string& value;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& data);
  std::istream& operator>>(std::istream& in, LabelIO&& data);
  std::istream& operator>>(std::istream& in, UllLiteralIO&& data);
  std::istream& operator>>(std::istream& in, DblScientificIO&& data);
  std::istream& operator>>(std::istream& in, StringIO&& data);

  std::istream& operator>>(std::istream& in, DataStruct& data);
  std::ostream& operator<<(std::ostream& out, const DataStruct& data);

  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
}

#endif
