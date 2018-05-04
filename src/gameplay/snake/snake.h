#ifndef SNAKE_IO_SNAKE_H
#define SNAKE_IO_SNAKE_H

#include <stdint.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_render.h>
//#include <SDL_image.h>

#include "../../standard/math/point.h"
#include "../../standard/list/list.h"

extern SDL_Renderer *get_renderer();

typedef struct snake {
    list_t body;
    unsigned char lenght;
    point_t direction;
} snake_t ;

typedef struct snake_node {
    point_t position;
    double angle;
} snake_node_t ;

void snake_init(snake_t *snake, size_t size, point_t *direction);

snake_node_t* snake_head(const snake_t* snake);

snake_node_t* snake_tail(const snake_t* snake);

void snake_grow(snake_t *snake);

void snake_diminish(snake_t *snake);

void change_dir(point_t* last_dir, char new_dir);

void snake_move(snake_t *snake);

bool snake_is_head(const snake_t* snake, const snake_node_t* node);

bool snake_is_tail(const snake_t* snake, const snake_node_t* node);

bool snake_collision(snake_t *snake, point_t *point);

bool snake_self_eating(snake_t *snake);


/* SDL */

bool snake_load_texture();

void snake_render(snake_t *snake);

#endif
