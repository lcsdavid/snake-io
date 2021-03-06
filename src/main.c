#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#ifdef __unix__

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>

#else

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>

#endif

#include "gameplay/appstate.h"

#define FRAME_PER_SEC 60
#define MILLIS_PER_FRAME 16

/* Game Ticks */
#define TICKS_PER_SEC 30
#define MILLIS_PER_TICKS 33

void close_(appstate_t *appstate);

void loop(appstate_t *appstate);

static int render_thread(void *arg) {
    appstate_t *appstate = arg;
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
    appstate_t *appstate = arg;
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
        unsigned int start_time, end_time;
        start_time = SDL_GetTicks();
        SDL_mutexP(appstate.lock);
        input(&appstate);
        SDL_mutexV(appstate.lock);
        end_time = SDL_GetTicks();
        if (end_time - start_time < 5)
            SDL_Delay(5 - end_time + start_time);
    }
    if (appstate.gamestate.multiplayer) {
        if (appstate.gamestate.player_one.score > appstate.gamestate.player_two.score)
            SDL_Log("Score joueur 1: %ld\nScore joueur 2: %ld\n Joueur 1 gagne!", appstate.gamestate.player_one.score,
                    appstate.gamestate.player_two.score);
        else
            SDL_Log("Score joueur 1: %ld\nScore joueur 2: %ld\n Joueur 2 gagne!", appstate.gamestate.player_one.score,
                    appstate.gamestate.player_two.score);
    } else
        SDL_Log("Score joueur 1: %ld", appstate.gamestate.player_one.score);


    close_(&appstate);
    return 0;
}

void close_(appstate_t *appstate) {
    SDL_DestroyRenderer(appstate->renderer);
    SDL_DestroyWindow(appstate->window);
    SDL_Quit();
}
