#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "snake/snake.h"

typedef struct {
    snake_t player_one;
    snake_t player_two;
    list_t elements;
    bool multiplayer;
} gamestate_t;

void gamestate_init(gamestate_t *gamestate);

bool point_taken(const gamestate_t* gamestate, const point_t* point);

point_t new_point(const gamestate_t *gamestate);

#endif
