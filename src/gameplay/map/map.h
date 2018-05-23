#ifndef SNAKE_IO_MAP_H
#define SNAKE_IO_MAP_H

#include "tile.h"

typedef struct map {
    unsigned short size_x;
    unsigned short size_y;
    tile_t **tiles;
} map_t;

void map_init(map_t* map, unsigned short size_x, unsigned short size_y);

map_t *map_create(unsigned short size_x, unsigned short size_y);



#endif
