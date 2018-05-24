project(learn-opencv)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(BUILD_SHARED_LIBS ON)

if(UNIX)
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -std=c++11")
    set(CMAKE_CXX_FLAGS_RELEASE "-W -Wall -O3 -std=c++11")
endif()

find_package(OpenCV)

add_subdirectory(ROI)
add_subdirectory(MaskCut)

#file(COPY ${CMAKE_SOURCE_DIR}/data/fruits.jpg DESTINATION ${CMAKE_BINARY_DIR}/bin/)
