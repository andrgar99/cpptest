#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/endian/conversion.hpp>

struct Package {
    std::string id;  // 4-character ID
    uint32_t size;   // Size of the package
    std::size_t offset; // Offset in the file
};

// Function to index packages using the mapped memory
std::vector<Package> indexPackagesWithMmap(const char* data, std::size_t size) {
    std::vector<Package> packages;

    const char* end = data + size;

    while (data < end) {
        // Read the 4-character ID
        if (data + 4 > end) break; // Ensure we don't read past the file
        std::string id(data, 4);
        data += 4;

        // Read the size (4 bytes, uint32_t)
        if (data + 4 > end) break;
        uint32_t packageSize = *reinterpret_cast<const uint32_t*>(data);
        boost::endian::big_to_native_inplace(packageSize);
        data += 4;

        // Record the package
        std::size_t offset = data - (end - size);
        packages.push_back({id, packageSize, offset});

        // Skip the package data
        data += packageSize;
    }

    return packages;
}

// Thread function to read a specific package
void readPackageFromMappedFile(const boost::interprocess::mapped_region& region, const std::string& targetId) {
    const char* data = static_cast<const char*>(region.get_address());
    std::size_t size = region.get_size();

    // Index all packages
    std::vector<Package> packages = indexPackagesWithMmap(data, size);

    // Find and read the specific package
    for (const auto& pkg : packages) {
        if (pkg.id == targetId) {
            const char* packageData = data + pkg.offset;
            std::vector<char> packageContent(packageData, packageData + pkg.size);

            // Print the package data
            std::cout << "Data for package " << targetId << ": ";
            for (char c : packageContent) {
                std::cout << c; // Print as characters (or process as needed)
            }
            std::cout << std::endl;
            return;
        }
    }

    std::cerr << "Package with ID " << targetId << " not found." << std::endl;
}

int creatMmap() {
    const std::vector<std::string> filenames = {"file1.bin", "file2.bin", "file3.bin"}; // Replace with your file names
    const std::string targetId = "PKG1"; // Replace with the desired package ID

    try {
        using namespace boost::interprocess;

        // Store memory-mapped regions for all files
        std::vector<mapped_region> mappedRegions;
        for (const auto& filename : filenames) {
            file_mapping fm(filename.c_str(), read_only);
            mappedRegions.emplace_back(fm, read_only);
        }

        // Launch threads to read from each mapped file
        std::vector<std::jthread> threads;
        for (const auto& region : mappedRegions) {
            threads.emplace_back(readPackageFromMappedFile, std::cref(region), targetId);
        }

        // Threads will automatically join when they go out of scope (std::jthread handles this)
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "Hello" << std::endl;
    return 0;
}