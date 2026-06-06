#ifndef INPUT_HPP
#define INPUT_HPP

#include <iosfwd>

namespace ulanova
{
  struct DelimiterIO
  {
    char expected;
  };

  std::istream & operator>>(std::istream & in, DelimiterIO && dest);
}

#endif
