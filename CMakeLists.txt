cmake_minimum_required(VERSION 3.9)
project(snake-io)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

file(GLOB_RECURSE SOURCE_FILES "src/*.c")

set(SDL2_PATH "lib/SDL2/win32/x86_64-w64-mingw32/")
set(SDL2_IMAGE_PATH "lib/SDL2_image/win32/x86_64-w64-mingw32/")
set(SDL2_TTF_PATH "lib/SDL2_ttf/win32/x86_64-w64-mingw32/")
set(SDL2_MIXER_PATH "lib/SDL2_mixer/win32/x86_64-w64-mingw32/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR})

add_executable(snake_io ${SOURCE_FILES} src/standard/collection/iterator.h src/gameplay/elements/element.h src/gameplay/elements/element.c)

target_link_libraries(snake_io ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES})