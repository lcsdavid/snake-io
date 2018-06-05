#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

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
#define TICKS_PER_SEC 30

#include "gameplay/appstate.h"
#include "gameplay/gamestate.h"

void close(appstate_t *appstate);
void loop(appstate_t *appstate);

int main(int argc, char *argv[]) {

    appstate_t appstate;
    if (!appstate_init(&appstate))
        return EXIT_FAILURE;
    unsigned int start_time, end_time;
    while (!appstate.end) {
        start_time = SDL_GetTicks();
        loop(&appstate);
        end_time = SDL_GetTicks();
        if(end_time - start_time < 200)
            SDL_Delay(200 - end_time + start_time);
    }
    close(&appstate);
    return 0;
}

void loop(appstate_t *appstate) {
    input(appstate);
    update(appstate);
    render(appstate);
}

void close(appstate_t *appstate) {
    SDL_DestroyRenderer(appstate->renderer);
    SDL_DestroyWindow(appstate->window);
    SDL_Quit();
}