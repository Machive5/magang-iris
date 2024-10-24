cmake_minimum_required(VERSION 3.10)

project(robot-position)
find_package(OpenCV REQUIRED)
add_executable(robot-position main.cpp)
target_link_libraries(robot-position ${OpenCV_LIBS})