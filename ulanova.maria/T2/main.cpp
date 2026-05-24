#include "data_struct.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

int main()
{
  using data_t = ulanova::DataStruct;
  using input_t = std::istream_iterator< data_t >;
  using output_t = std::ostream_iterator< data_t >;

  std::vector< data_t > data;
  
  std::copy(input_t{std::cin}, input_t{}, std::back_inserter(data));
  std::sort(data.begin(), data.end());
  std::copy(data.begin(), data.end(), output_t{std::cout, "\n"});


  return 0;
}
