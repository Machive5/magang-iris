cmake_minimum_required(VERSION 3.10)

project(jarak-benda)
find_package(OpenCV REQUIRED)
add_executable(jarak-benda main.cpp)
target_link_libraries(jarak-benda ${OpenCV_LIBS})