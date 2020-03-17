# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("hls-media-stream")

# Include sub-projects.
add_subdirectory ("oatpp")
add_subdirectory ("hls-media-stream")

