#include "input.hpp"

#include <istream>

std::istream & ulanova::operator>>(std::istream & in, DelimiterIO && dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  char current = 0;
  in >> current;

  if (current != dest.expected)
  {
    in.setstate(std::ios_base::failbit);
  }

  return in;
}
