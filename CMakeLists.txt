cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
	cmake_policy(SET CMP0048 OLD)
endif()

project(glhl)
set(PROJECT_VERSION "alpha_0.0.0")
enable_testing()

# Library Projects
add_subdirectory(src)

# Examples
add_subdirectory(examples)