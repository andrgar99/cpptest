
#define CL_TARGET_OPENCL_VERSION 300
#include "header.h"





// template short swap_endian(short);


int16_t swap_endian2(int16_t val)
{
    return boost::endian::endian_reverse(val);
}



void byteswap_vector(std::vector<int16_t>& data)
{
    std::for_each(std::execution::par, data.begin(), data.end(), [](int16_t& n) {
        boost::endian::endian_reverse_inplace(n);
    });
}