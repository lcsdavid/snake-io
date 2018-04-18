#ifndef SNAKE_IO_SNAKE_H
#define SNAKE_IO_SNAKE_H

#include <stdint.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "../../sdl/sdl.h"

#include "../../standard/math/point.h"
#include "../../standard/list/list.h"

typedef struct snake {
    list_t body;
    unsigned char lenght;
    point_t direction;
} snake_t ;

typedef enum body_type {
    HEAD, BODY, TAIL
} body_type_t ;

typedef struct snake_body {
    point_t *position;
    body_type_t type;
} snake_body_t ;

void snake_grow(snake_t *snake);

void snake_diminish(snake_t *snake);

void change_dir(point_t* last_dir, char new_dir);

void snake_move(snake_t *snake);

/* SDL */

void snake_load_texture();

void snake_render(const snake_t *snake);

#endif
