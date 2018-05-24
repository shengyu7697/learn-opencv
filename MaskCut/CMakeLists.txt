project(mask_cut)
cmake_minimum_required(VERSION 3.0)

find_package(OpenCV)

file(GLOB SRCS *.cpp)
add_executable(mask_cut ${SRCS})

target_include_directories(mask_cut PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(mask_cut ${OpenCV_LIBS})
