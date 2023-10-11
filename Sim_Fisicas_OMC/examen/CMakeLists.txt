cmake_minimum_required(VERSION 3.26)
project(examen)

set(CMAKE_CXX_STANDARD 17)

add_executable(examen main.cpp)
find_package(box2d CONFIG REQUIRED)
target_link_libraries(examen PRIVATE box2d::box2d)