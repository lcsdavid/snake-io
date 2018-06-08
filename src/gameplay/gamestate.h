#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "snake/snake.h"
#include "elements/element.h"

typedef struct {
    snake_t player_one;
    snake_t player_two;
    list_t elements;
    bool multiplayer;
    bool gameover;
    bool fullscreen;
    int difficulte;
} gamestate_t;

void gamestate_init(gamestate_t *gamestate);

void gamestate_render(gamestate_t *gamestate, SDL_Renderer *renderer);

bool collision(gamestate_t *gamestate);

bool gestion_collision(gamestate_t *gamestate, element_t *element, snake_t *snake);

bool point_taken(const gamestate_t* gamestate, const point_t* point);

point_t new_point(const gamestate_t *gamestate);

#endif
