cmake_minimum_required(VERSION 3.10)

# Project name
project(ThreadExample)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the compiler (optional, replace with your desired compiler)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")

# Enable performance optimizations
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -mtune=native")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include) # Add the include folder
include_directories(/usr/include)               # Include Boost headers (if needed)

# Automatically find all .cpp files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Add executable with all source files
add_executable(threading ${SOURCES})

# Link OpenCL and TBB libraries
target_link_libraries(threading OpenCL tbb)


#sudo apt install ninja-build
#cmake -G Ninja ..
#ninja -j$(nproc)