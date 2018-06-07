#ifndef APPSTATE_H
#define APPSTATE_H

#include <stdbool.h>
#include <time.h>

#include <SDL_mutex.h>
#include <SDL_render.h>
#include <SDL_video.h>

typedef struct gamestate gamestate_t;

typedef struct appstate {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_mutex* lock;

    gamestate_t* gamestate;

    bool end;
} appstate_t;

bool appstate_init(appstate_t *appstate);

void input(appstate_t *appstate);

void update(appstate_t *appstate);

void render(appstate_t *appstate);

#endif