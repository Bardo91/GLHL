cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
cmake_policy(SET CMP0048 OLD)
endif()
project(frameBuffer)

# Collect all sources
file(GLOB_RECURSE FRAMEBUFFER_SOURCE_FILES "src/*.cpp" "src/*.h" "src/*.inl")

# Compiler specific options
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

# Library
add_executable(frameBuffer ${FRAMEBUFFER_SOURCE_FILES})
target_include_directories(frameBuffer PUBLIC ../../src)
target_link_libraries(frameBuffer LINK_PUBLIC glhl)

file(COPY "src/shaders" DESTINATION ${PROJECT_BINARY_DIR})
