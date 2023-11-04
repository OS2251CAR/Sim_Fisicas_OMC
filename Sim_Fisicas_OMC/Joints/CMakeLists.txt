cmake_minimum_required(VERSION 3.26)
project(Joints)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

find_package(box2d CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(Joints main.cpp)

target_link_libraries(Joints PRIVATE sfml-system sfml-window sfml-graphics sfml-audio box2d::box2d)

