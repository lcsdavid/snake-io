#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include <SDL.h>
#include "sdl/sdl.h"

void input();
void render();
void update();

int main(int argc, char *argv[]) {
    if (!init()){
        return -1;
    }
    printf("entrée dans la boucle \n");
    while (!SDL_HasEvent(SDL_QUIT)) {

    }
    close();
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
