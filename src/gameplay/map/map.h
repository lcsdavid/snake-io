#ifndef SNAKE_IO_MAP_H
#define SNAKE_IO_MAP_H

#include <cassert>

#include "tile.h"

typedef struct map {
    unsigned short size_x;
    unsigned short size_y;
    tile_t tiles[size_x][size_y];
} map_t;

void map_init(map_t* map, unsigned short size_x, unsigned short size_y);

map_t *map_create(unsigned short size_x, unsigned short size_y);



#endif
