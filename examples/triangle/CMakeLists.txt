cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
cmake_policy(SET CMP0048 OLD)
endif()
project(triangle)

# Collect all sources
file(GLOB_RECURSE TRIANGLE_SOURCE_FILES "src/*.cpp" "src/*.h" "src/*.inl")

# Compiler specific options
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

find_path(GLEW_INCLUDE_DIR GL/glew.h HINTS "C:/glew/include")
find_library(GLEW_LIBRARY NAMES GLEW glew32 glew glew32s HINTS "C:/glew/lib/Release/Win32")

# Library
add_executable(triangle ${TRIANGLE_SOURCE_FILES})
target_include_directories(triangle PUBLIC ../../src)
target_link_libraries(triangle LINK_PUBLIC glhl)

file(COPY "src/shaders" DESTINATION ${PROJECT_BINARY_DIR})
