# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(HTTP_Proxy_Server VERSION 1.0.0.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the output directories for binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Include the directory containing header files
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the executable
# Find all source files in the src directory
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cc")

# Add executable target from source files
add_executable(${PROJECT_NAME} ${SOURCES})

# Specify where to find the libraries if you are linking with any
# link_directories(${CMAKE_SOURCE_DIR}/lib)

# Example for linking libraries (if you have any custom or external libraries)
# target_link_libraries(${PROJECT_NAME} YourLibraryName)

# Optional: if you want to organize by debug/release builds
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin/release)
