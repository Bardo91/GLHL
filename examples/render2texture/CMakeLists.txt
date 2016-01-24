cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
cmake_policy(SET CMP0048 OLD)
endif()
project(render2texture)

# Collect all sources
file(GLOB_RECURSE RENDER2TEXTURE_SOURCE_FILES "src/*.cpp" "src/*.h" "src/*.inl")

# Compiler specific options
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

# Library
add_executable(render2texture ${RENDER2TEXTURE_SOURCE_FILES})
target_include_directories(render2texture PUBLIC ../../src)
target_link_libraries(render2texture LINK_PUBLIC glhl)