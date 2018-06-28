project(least_squares)
cmake_minimum_required(VERSION 3.0)

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SRCS *.cpp)
add_executable(least_squares ${SRCS})
target_link_libraries(least_squares ${OpenCV_LIBS})
