#ifndef SNAKE_IO_INPUT_H
#define SNAKE_IO_INPUT_H

#include <SDL_events.h>
#include "gameplay/snake/snake.h"

extern snake_t *get_player1();
extern snake_t *get_player2();

#define P1_LEFT 0
#define P1_RIGHT 1

#define P2_LEFT 2
#define P2_RIGHT 3

void input();

void keyboard_input(SDL_Event event);

#endif
