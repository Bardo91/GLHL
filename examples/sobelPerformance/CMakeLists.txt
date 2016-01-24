cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
cmake_policy(SET CMP0048 OLD)
endif()
project(sobelPerformance)

# Collect all sources
file(GLOB_RECURSE SOBELPERFORMANCE_SOURCE_FILES "src/*.cpp" "src/*.h" "src/*.inl")

# Compiler specific options
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

# Library
add_executable(sobelPerformance ${SOBELPERFORMANCE_SOURCE_FILES})
target_include_directories(sobelPerformance PUBLIC ../../src)
target_link_libraries(sobelPerformance LINK_PUBLIC glhl)