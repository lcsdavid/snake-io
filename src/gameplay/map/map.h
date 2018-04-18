#ifndef SNAKE_IO_MAP_H
#define SNAKE_IO_MAP_H

#include "../tile.h"

typedef struct map {
    unsigned int size_x;
    unsigned int size_y;
    tile_t **tiles;
};

#endif
