project(roi_mask)
cmake_minimum_required(VERSION 3.0)

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SRCS *.cpp)
add_executable(roi_mask ${SRCS})
target_link_libraries(roi_mask ${OpenCV_LIBS})
