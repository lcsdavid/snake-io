cmake_minimum_required(VERSION 3.9)
project(snake-io)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

file(GLOB_RECURSE SOURCE_FILES "src/*.c")

set(SDL2_PATH "lib/SDL2/win32/x86_64-w64-mingw32/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(snake_io ${SOURCE_FILES})

target_link_libraries(snake_io ${SDL2_LIBRARY})