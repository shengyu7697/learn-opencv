project(FFT)
cmake_minimum_required(VERSION 3.0)

find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})

file(GLOB SRCS *.cpp)
add_executable(fft ${SRCS})
target_link_libraries(fft ${OpenCV_LIBS})
