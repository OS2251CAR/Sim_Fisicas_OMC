cmake_minimum_required(VERSION 3.26)
project(holaJupiter)

set(CMAKE_CXX_STANDARD 17)

add_executable(holaJupiter main.cpp)
find_package(box2d CONFIG REQUIRED)
target_link_libraries(holaJupiter PRIVATE box2d::box2d)
