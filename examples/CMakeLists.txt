cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
	cmake_policy(SET CMP0048 OLD)
endif()

# Examples
add_subdirectory(contextCreation)
add_subdirectory(frameBuffer)
add_subdirectory(loadTexture)
add_subdirectory(particleFilter)
add_subdirectory(render2texture)
add_subdirectory(sobelPerformance)
add_subdirectory(testX11)
add_subdirectory(triangle)