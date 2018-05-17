project(svd)
cmake_minimum_required(VERSION 3.0)

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SRCS *.cpp)
add_executable(svd ${SRCS})
target_link_libraries(svd ${OpenCV_LIBS})
