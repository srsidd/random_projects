cmake_minimum_required(VERSION 2.8.12)

project(demo)
project(face3)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(demo demo.cpp)
target_link_libraries(demo ${OpenCV_LIBS})

add_executable(face3 face3.cpp)
target_link_libraries(face3 ${OpenCV_LIBS})
