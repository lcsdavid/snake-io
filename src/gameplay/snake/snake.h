#ifndef SNAKE_IO_SNAKE_H
#define SNAKE_IO_SNAKE_H

#include <stdint.h>
#include <stdio.h>

#ifdef __unix__

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

#else

#include <SDL.h>
#include <SDL_render.h>
#include <SDL_image.h>

#endif



#include "../../standard/math/point.h"
#include "../../standard/collection/list.h"
#include "../../standard/collection/queue.h"

#define SNAKE_TEXTURE_SIZE_X 32
#define SNAKE_TEXTURE_SIZE_Y 32
#define SNAKE_BODY_DIAMETER 32
#define SPEED 5

typedef struct snake {
    list_t body;
    unsigned char lenght;
    long score;
} snake_t ;

typedef struct snake_node {
    point_t position;
    double angle;
} snake_node_t ;

snake_node_t *snake_node_create(const point_t *point, double angle);

void snake_init(snake_t *snake, const point_t *position, double direction);

snake_node_t* snake_head(const snake_t* snake);

snake_node_t* snake_tail(const snake_t* snake);

void snake_grow(snake_t *snake);

void snake_diminish(snake_t *snake);

void snake_change_direction(snake_t *snake, bool gauche);

bool snake_move(snake_t *snake);

bool snake_is_head(const snake_t* snake, const snake_node_t* node);

bool snake_is_tail(const snake_t* snake, const snake_node_t* node);

bool snake_collision(snake_t *snake, point_t *point);

bool snake_self_eating(snake_t *snake);


/* SDL */

bool snake_load_texture(SDL_Renderer *renderer);

void snake_free_texture(SDL_Renderer *renderer);

void snake_render(snake_t *snake, SDL_Renderer *renderer, bool secondSnake);

#endif
