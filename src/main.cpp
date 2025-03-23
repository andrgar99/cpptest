#include "header.h"




int main(int argc, char* argv[])
{
    using namespace boost::endian;
    // Check if an integer argument is provided
    // if (argc < 2) {
    //     std::cerr << "Usage: " << argv[0] << " <integer>" << std::endl;
    //     return 1;
    // }

    float c = 2.2f;
    endian_reverse_inplace(c);

    std::cout << c << std::endl;


    // print();

    int a = creatMmap();
    return 0;
}