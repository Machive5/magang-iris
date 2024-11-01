cmake_minimum_required(VERSION 3.10)

project(object-detection)
find_package(OpenCV REQUIRED)
add_executable(object-detection main.cpp)
target_link_libraries(object-detection ${OpenCV_LIBS})