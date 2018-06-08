#ifndef SNAKE_IO_ELEMENT_H
#define SNAKE_IO_ELEMENT_H

#include "../../standard/math/point.h"
#include "../snake/snake.h"

#define ELEMENT_APPLE 0
#define ELEMENT_BOMBE 1
#define ELEMENT_WALL 2
#define ELEMENT_LASER 3

typedef struct element {
    point_t position;
    int type;
} element_t;

void element_init(element_t *element, const point_t* position, int type);

element_t *element_create(const point_t* position, int type);

void element_effect(element_t* element, snake_t* snake);

void element_render(element_t* element, SDL_Renderer* renderer);

bool element_load_texture(SDL_Renderer *renderer);

#endif
