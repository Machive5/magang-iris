cmake_minimum_required(VERSION 3.10)

project(posisi-robot)
find_package(OpenCV REQUIRED)
add_executable(posisi-robot main.cpp)
target_link_libraries(posisi-robot ${OpenCV_LIBS})