#ifndef SNAKE_IO_ELEMENT_H
#define SNAKE_IO_ELEMENT_H

#include "../../standard/math/point.h"
#include "../snake/snake.h"

#define ELEMENT_APPLE 1
#define ELEMENT_BOMBE 2
#define ELEMENT_WALL 3

typedef struct element {
    point_t position;
    int type;
    void (*element_effect)(snake_t *);
    void (*element_render)(SDL_Renderer*);
} element_t;

void element_init(element_t *element, const point_t* position, int type);

element_t *element_create(const point_t* position, int type);

void element_effect_apple(element_t *element, snake_t *snake);
void element_effect_bombe(element_t *element, snake_t *snake);
void element_effect_wall(element_t *element, snake_t *snake);

bool collision(snake_t *snake, element_t *elem);

void element_render_apple(SDL_Renderer* renderer);

void element_render_bombe(SDL_Renderer* renderer);

void element_render_wall(SDL_Renderer* renderer);

void element_load_texture(SDL_Renderer *renderer);

#endif
