#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "snake/snake.h"

typedef struct {
    snake_t player_one;
    snake_t player_two;
    list_t elements;
    bool multiplayer;
<<<<<<< HEAD
    bool gameover;
=======
    bool fullscreen;
>>>>>>> 68444a2d4960643e0cc70d5ca7ae832785b682ac
} gamestate_t;

void gamestate_init(gamestate_t *gamestate);

void gamestate_render(gamestate_t *gamestate, SDL_Renderer *renderer);

void collision(gamestate_t *gamestate);


bool point_taken(const gamestate_t* gamestate, const point_t* point);

point_t new_point(const gamestate_t *gamestate);

#endif
