#ifndef APPSTATE_H
#define APPSTATE_H

#include <time.h>

#include "gamestate.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool end;
    gamestate_t gamestate;
} appstate_t;

bool appstate_init(appstate_t *appstate);

void input(appstate_t *appstate);

void update(appstate_t *appstate);

void render(appstate_t *appstate);

#endif