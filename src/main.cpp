#include "header.h"






int main(int argc, char* argv[])
{
    // Check if an integer argument is provided
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <integer>" << std::endl;
        return 1;
    }

    // Parse the integer from the command line
    std::string ascii_string = argv[1];
    uint64_t value = boost::lexical_cast<uint64_t>(ascii_string);
    std::cout << "Input value: " << value << std::endl;

    // Generate random data on the host
    std::vector<int16_t> host_vector2(value);
    std::generate(host_vector2.begin(), host_vector2.end(), rand);

    // Time byteswap_vector_gpu
    auto start_gpu = std::chrono::high_resolution_clock::now();
    byteswap_vector_gpu(host_vector2);
    auto end_gpu = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_gpu = end_gpu - start_gpu;
    std::cout << "GPU byte swap time: " << elapsed_gpu.count() << " seconds" << std::endl;

    // Time byteswap_vector
    auto start_cpu = std::chrono::high_resolution_clock::now();
    byteswap_vector(host_vector2);
    auto end_cpu = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_cpu = end_cpu - start_cpu;
    std::cout << "CPU byte swap time: " << elapsed_cpu.count() << " seconds" << std::endl;


    std::cout << "Done!" << std::endl;

    return 0;
}