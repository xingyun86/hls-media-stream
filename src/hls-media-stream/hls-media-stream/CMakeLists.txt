cmake_minimum_required (VERSION 3.8)

set(project_name hls-media-stream) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib STATIC 
        hls-media-stream/AppComponent.hpp
        hls-media-stream/Utils.cpp
        hls-media-stream/Utils.hpp
        hls-media-stream/controller/MediaController.cpp
        hls-media-stream/controller/MediaController.hpp
        hls-media-stream/hls/Playlist.cpp
        hls-media-stream/hls/Playlist.hpp
)

target_include_directories(${project_name}-lib
        PUBLIC hls-media-stream
)

## link libs
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/oatpp)
#find_package(oatpp 1.0.0 REQUIRED)

# 把第三方库的.a文件和.so文件放到代码的lib文件夹
link_directories(${CMAKE_BINARY_DIR}/oatpp)

if (MSVC)
	list(APPEND uSockets_cflags /W4)
	list(APPEND uSockets_defines WIN32_LEAN_AND_MEAN _WIN32_WINNT=0x0501)
	MESSAGE(STATUS "CMAKE_BUILD_TYPE=" ${CMAKE_BUILD_TYPE})

	set(CompilerFlags
		CMAKE_CXX_FLAGS
		CMAKE_CXX_FLAGS_DEBUG
		CMAKE_CXX_FLAGS_RELEASE
		CMAKE_C_FLAGS
		CMAKE_C_FLAGS_DEBUG
		CMAKE_C_FLAGS_RELEASE
		)
	foreach(CompilerFlag ${CompilerFlags})
		string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
	endforeach()
endif(MSVC)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp
        PUBLIC oatpp-test
)

add_definitions(
        -DEXAMPLE_MEDIA_FOLDER="${CMAKE_CURRENT_LIST_DIR}/video"
)

## add executables

add_executable(${project_name}-exe
        hls-media-stream/App.cpp
)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

