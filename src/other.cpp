
#define CL_TARGET_OPENCL_VERSION 300
#include "header.h"


#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/functional/math.hpp>
#include <boost/endian/conversion.hpp>
#include <boost/compute/types/complex.hpp>
#include <boost/compute/types/builtin.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/accumulate.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/types/builtin.hpp>
#include <boost/compute/lambda.hpp>


namespace compute = boost::compute;

void computevector(std::vector<float>& data)
{
    compute::device device = compute::system::default_device();
    compute::context context(device);
    compute::command_queue queue(context, device);


    std::for_each(std::execution::par, data.begin(), data.end(), [&](float& n) { 
        n = 9; 
    });

    compute::vector<float> device_vector(data.size(), context);



    // transfer data from the host to the device
    compute::copy(
        data.begin(), data.end(), device_vector.begin(), queue
    );
    // calculate the square-root of each element in-place
    
    compute::transform(
        device_vector.begin(),
        device_vector.end(),
        device_vector.begin(),
        compute::sqrt<float>(),
        queue
    );


    // copy values back to the host
    compute::copy(
        device_vector.begin(), device_vector.end(), data.begin(), queue
    );
    
}

void byteswap_vector_gpu(std::vector<int16_t>& data)
{
    compute::device device = compute::system::default_device();
    compute::context context(device);
    compute::command_queue queue(context, device);




    compute::vector<int16_t> device_vector(data.size(), context);



    // transfer data from the host to the device
    compute::copy(
        data.begin(), data.end(), device_vector.begin(), queue
    );
    // calculate the square-root of each element in-place
    

    BOOST_COMPUTE_FUNCTION(int16_t, add_four, (int16_t x),
    {
        return (x << 8) | (x >> 8);
    });
    

    using boost::compute::lambda::_1;
    using boost::compute::lambda::_2;

    compute::transform(
        device_vector.begin(),
        device_vector.end(),
        device_vector.begin(),
        _1 < 8,
        queue
    );


    // copy values back to the host
    compute::copy(
        device_vector.begin(), device_vector.end(), data.begin(), queue
    );
}

void byteswap_vector(std::vector<int16_t>& data)
{
    std::for_each(std::execution::par, data.begin(), data.end(), [](int16_t& n) {
        boost::endian::endian_reverse_inplace(n);
    });
}

