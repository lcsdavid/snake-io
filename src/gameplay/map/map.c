#include "map.h"

bool map_init(map_t* map, unsigned short size_x, unsigned short size_y) {
    assert(map);
    map->size_x = size_x;
    map->size_y = size_y;
    map->tiles = calloc(size_x, sizeof(tile_t*));
    if(!map->tiles) {
        perror("calloc():");
        return false;
    }
    for(size_t x = 0; x < size_x; x++) {
        map->tiles[x] = calloc(size_y, sizeof(tile_t));
        if(!map->tiles[x]) {
            perror("calloc():");
            return false;
        }
        for(size_t y = 0; y < size_y; y++) {
            int floor = rand() % 4;
            switch (floor) {
                case 0:
                    map->tiles[x][y] = TILE_FLOOR_1;
                    break;
                case 1:
                    map->tiles[x][y] = TILE_FLOOR_2;
                    break;
                case 2:
                    map->tiles[x][y] = TILE_FLOOR_3;
                    break;
                case 3:
                    map->tiles[x][y] = TILE_FLOOR_4;
                    break;
                default:
                    map->tiles[x][y] = TILE_UNDEFINED;
                    break;
            }
        }
    }
    return true;
}

map_t *map_create(unsigned short size_x, unsigned short size_y) {
    map_t* map = calloc(1, sizeof(map_t));
    if(!map) {
        perror("calloc():");
        return NULL;
    }
    map_init(map, size_x, size_y);
    return map;
}

bool map_load_from_file(map_t* map, char file_path[]) {
    assert(map);
    FILE* file = fopen(file_path, "r");
    int x, y;
    fscanf(file, "%d %d\n", &x, &y);
    map_init(map, x, y);
    int c;
    x = 0;
    y = 0;
    do {
        c = getc(file);
        if(c == 'X') {
            // WALL
        }
        x++;
        if(c == '\n') {
            y++;
            x = 0;
        }
    } while(c == EOF);
    fclose(file);
}