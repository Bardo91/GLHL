cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
cmake_policy(SET CMP0048 OLD)
endif()
project(testX11)

# Collect all sources
file(GLOB_RECURSE TESTX11_SOURCE_FILES "src/*.cpp" "src/*.h" "src/*.inl")

# Compiler specific options
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

# Library
add_executable(testX11 ${TESTX11_SOURCE_FILES})
target_include_directories(testX11 PUBLIC ../../src)
target_link_libraries(testX11 glhl)