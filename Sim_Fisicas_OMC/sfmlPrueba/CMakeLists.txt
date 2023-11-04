cmake_minimum_required(VERSION 3.26)
project(sfmlPrueba)

set(CMAKE_CXX_STANDARD 17)

add_executable(sfmlPrueba main.cpp)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)

target_link_libraries(sfmlPrueba PRIVATE sfml-system sfml-network sfml-graphics sfml-window box2d::box2d)

