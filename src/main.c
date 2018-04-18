#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include <SDL.h>

#include "sdl/sdl.h"

void input();
void render();
void update();

int main(int argc, char *argv[]) {
    ren
    if (!sdl_init())
        return -1;
    while (!SDL_HasEvent(SDL_QUIT)) {

    }
    sdl_close(window);
    return 0;
}

void input() {
    SDL_Event event;
    if(!SDL_PollEvent(&event))
        return;
    switch(event.type) {
        default:
            break;
    }
}
