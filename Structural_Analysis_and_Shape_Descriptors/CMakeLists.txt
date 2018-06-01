project(Structural_Analysis_and_Shape_Descriptors)
cmake_minimum_required(VERSION 3.0)

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SRCS *.cpp)
add_executable(Structural_Analysis_and_Shape_Descriptors ${SRCS})
target_link_libraries(Structural_Analysis_and_Shape_Descriptors ${OpenCV_LIBS})
