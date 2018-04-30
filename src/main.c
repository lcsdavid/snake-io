#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include <SDL.h>
#include "sdl/sdl.h"
#include "gameplay/snake/snake.h"

void input();
void render();
void update();


int main(int argc, char *argv[]) {
    snake_t snake1, snake2;
    snake_init(&snake1);
    snake_init(&snake2);
    if (!init()){
        return -1;
    }

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
