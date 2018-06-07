#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <time.h>

#include "gameplay/snake/snake.h"
#include "standard/math/point.h"
#include "standard/collection/list_iterator.h"
#include "standard/collection/list.h"
#include "gameplay/elements/element.h"
#include "standard/collection/node.h"

#define FRAME_PER_SEC 60
#define MILLIS_PER_FRAME 5

/* Game Ticks */
#define TICKS_PER_SEC 30
#define MILLIS_PER_TICKS 100

#include "gameplay/appstate.h"
#include "gameplay/gamestate.h"

void close(appstate_t *appstate);
void loop(appstate_t *appstate);

static int render_thread(void *arg) {
    appstate_t* appstate = arg;
    while (!appstate->end) {
        unsigned int start_time, end_time;
        start_time = SDL_GetTicks();
        SDL_mutexP(appstate->lock);
        render(appstate);
        SDL_mutexV(appstate->lock);
        end_time = SDL_GetTicks();
        if (end_time - start_time < MILLIS_PER_FRAME) {
            SDL_Delay(MILLIS_PER_FRAME - end_time + start_time);
        }
    }
    return 0;
}

static int update_thread(void *arg) {
    appstate_t* appstate = arg;
    while (!appstate->end) {
        unsigned int start_time, end_time;
        start_time = SDL_GetTicks();
        SDL_mutexP(appstate->lock);
        update(appstate);
        SDL_mutexV(appstate->lock);
        end_time = SDL_GetTicks();
        if (end_time - start_time < MILLIS_PER_TICKS)
            SDL_Delay(MILLIS_PER_TICKS - end_time + start_time);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    appstate_t appstate;
    if (!appstate_init(&appstate))
        return EXIT_FAILURE;
    appstate.lock = SDL_CreateMutex();
    SDL_Thread *r_thread = SDL_CreateThread(&render_thread, "RenderingThread", &appstate);
    SDL_Thread *i_thread = SDL_CreateThread(&update_thread, "UpdateThread", &appstate);
    while (!appstate.end) {
        SDL_mutexP(appstate.lock);
        input(&appstate);
        SDL_mutexV(appstate.lock);
    }
    close(&appstate);
    return 0;
}

void close(appstate_t *appstate) {
    SDL_DestroyRenderer(appstate->renderer);
    SDL_DestroyWindow(appstate->window);
    SDL_Quit();
}