#ifndef SNAKE_IO_MAP_H
#define SNAKE_IO_MAP_H

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "tile.h"

typedef struct map {
    unsigned short size_x;
    unsigned short size_y;
    tile_t** tiles;
} map_t;

bool map_init(map_t* map, unsigned short size_x, unsigned short size_y);

map_t *map_create(unsigned short size_x, unsigned short size_y);

bool map_load_from_file(map_t* map, char file_path[]);

#endif
