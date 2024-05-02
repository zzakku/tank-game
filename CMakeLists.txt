cmake_minimum_required(VERSION 3.20)
project(RaylibTest LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(raylib)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/res/player.png
        ${CMAKE_CURRENT_BINARY_DIR}/res COPYONLY)
add_executable(hello "hello.cpp")
target_link_libraries(hello raylib)
