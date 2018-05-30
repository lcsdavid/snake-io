#ifndef SNAKE_IO_TILE_H
#define SNAKE_IO_TILE_H

#include <assert.h>

#include <SDL_render.h>

#define TILE_SIZE 16

typedef enum {
    TILE_FLOOR_1,
    TILE_FLOOR_2,
    TILE_FLOOR_3,
    TILE_FLOOR_4,
    TILE_WALL,
    TILE_UNDEFINED
} tile_t;



void tile_render(tile_t tile, SDL_Renderer* renderer);

#endif
