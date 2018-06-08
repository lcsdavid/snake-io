#ifndef APPSTATE_H
#define APPSTATE_H

#include <time.h>

#ifdef __unix__

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#else

#include <SDL_ttf.h>
#include <SDL_mixer.h>

#endif

#include "gamestate.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_mutex* lock;
    bool end;
    gamestate_t gamestate;
} appstate_t;

bool appstate_init(appstate_t *appstate);

void input(appstate_t *appstate);

void update(appstate_t *appstate);

void render(appstate_t *appstate);

#endif