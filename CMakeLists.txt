cmake_minimum_required(VERSION 3.9)
project(snake-io)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES src/main.c
        src/standard/arrays/vector/vector.c
        src/standard/linked_list/node/node.h
        src/standard/linked_list/queue/queue.c
        src/standard/linked_list/stack/stack.c
        src/standard/math/point.c
        src/standard/linked_list/node/slnode.c src/standard/linked_list/node/dlnode.h src/standard/linked_list/node/dlnode.c)

add_executable(snake_io ${SOURCE_FILES})
