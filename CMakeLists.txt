cmake_minimum_required(VERSION 3.9)
project(snake-io)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES src/main.c
        #src/array/vector/vector.c
        src/list/queue/queue.c
        #src/math/point.c
        )

add_executable(snake_io ${SOURCE_FILES})
