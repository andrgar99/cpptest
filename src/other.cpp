
#define CL_TARGET_OPENCL_VERSION 300
#include "header.h"



#include <boost/endian/conversion.hpp>






void byteswap_vector(std::vector<int16_t>& data)
{
    std::for_each(std::execution::par, data.begin(), data.end(), [](int16_t& n) {
        boost::endian::endian_reverse_inplace(n);
    });
}