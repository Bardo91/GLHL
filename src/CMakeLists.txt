cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
cmake_policy(SET CMP0048 OLD)
endif()
project(glhl)

# Collect all sources
file(GLOB_RECURSE GLHL_SOURCE_FILES "glhl/*.cpp" "glhl/*.h" "glhl/*.inl")

# Clasify sources according to folder structure.
# This creates a nice layout for the project in visual studio
# This macro is courtesy of http://www.cmake.org/pipermail/cmake/2013-November/056336.html
macro(GroupSources curdir)
	file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
		${PROJECT_SOURCE_DIR}/${curdir}/*)
	foreach(child ${children})
		if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			GroupSources(${curdir}/${child})
		else()
			string(REPLACE "/" "\\" groupname ${curdir})
			source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
		endif()
	endforeach()
endmacro()

GroupSources(glhl)

# Compiler specific options
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

# Find the OpenGL Extension Wrangler Library (GLEW)
#####find_package(GLEW REQUIRED) TODO: auto find_file
find_path(GLEW_INCLUDE_DIR GL/glew.h HINTS "C:/glew/include")
find_library(GLEW_LIBRARY NAMES GLEW glew32 glew glew32s HINTS "C:/glew/lib/Release/Win32")

find_path(SOIL_INCLUDE_DIR soil.h HINTS "C:/soil")
find_library(SOIL_LIBRARY NAMES soil HINTS "C:/soil")

# Library
add_library(glhl STATIC ${GLHL_SOURCE_FILES})
target_include_directories(glhl PUBLIC ${PROJECT_SOURCE_DIR}/glhl)
target_include_directories(glhl PUBLIC ${GLEW_INCLUDE_DIR})
target_include_directories(glhl PUBLIC ${SOIL_INCLUDE_DIR})
target_link_libraries(glhl LINK_PUBLIC ${GLEW_LIBRARY})
target_link_libraries(glhl LINK_PUBLIC ${SOIL_LIBRARY})
target_link_libraries(glhl LINK_PUBLIC opengl32 glu32)