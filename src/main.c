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
    snake_t *snake1, *snake2;
    snake1 = malloc(sizeof(snake_t));
    snake2 = malloc(sizeof(snake_t));
    snake_init(snake1);
    snake_init(snake2);
    if (!init()){
        return -1;
    }

    while (!SDL_HasEvent(SDL_QUIT)) {
        snake_move(snake1);
        snake_render(snake1);
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
