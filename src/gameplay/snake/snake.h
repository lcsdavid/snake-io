#ifndef SNAKE_IO_SNAKE_H
#define SNAKE_IO_SNAKE_H

#include <stdint.h>

#include "../../standard/queue/queue.h"

typedef struct snake {
    queue_t body;
    uint8_t lenght;
    double /* type ? */ direction;
} snake_t ;

void snake_grow(snake_t *snake);

void snake_diminish(snake_t *snake);

void snake_move(snake_t *snake, double direction /* type ? */);

void snake_draw(const snake_t *snake);

#endif
