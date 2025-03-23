#ifndef HEADER_H
#define HEADER_H



#include <execution>
#include <algorithm>
#include <vector>

#include <cstdlib>
#include <iostream>
#include <boost/lexical_cast.hpp>


void print();
void computevector(std::vector<float>& data);

void byteswap_vector_gpu(std::vector<int16_t>& data);
void byteswap_vector(std::vector<int16_t>& data);

#endif