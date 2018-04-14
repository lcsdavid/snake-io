cmake_minimum_required(VERSION 3.9)
project(snake-io)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(PROJECT_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCE_FILES "src/*.c")

add_executable(snake_io ${SOURCE_FILES})
