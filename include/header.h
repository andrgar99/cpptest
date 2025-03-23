#ifndef HEADER_H
#define HEADER_H



#include <execution>
#include <algorithm>
#include <vector>

#include <cstdlib>
#include <iostream>



#include <boost/endian/conversion.hpp>
#include <type_traits>




int16_t swap_endian2(int16_t val);
void print();
void byteswap_vector(std::vector<int16_t>& data);

#endif