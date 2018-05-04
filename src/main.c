#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include <SDL.h>
#include "gameplay/snake/snake.h"

SDL_Window* window;
SDL_Renderer* renderer;

snake_t snake_1, snake_2;

bool init();
void input();
void render();
void update();
void close();

int main(int argc, char *argv[]) {
    /* snake_load_texture();
    snake_init(&snake_1, 3, NULL); */
    // snake_init(&snake2, 2, &(point_t){2,1});
    if (!init()) return -1;
    while (!SDL_HasEvent(SDL_QUIT)) {
        //update();
        render();
    }
    close();
    return 0;
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init(): %s\n", SDL_GetError());
        return false;
    }
    atexit(SDL_Quit);
    /*if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        fprintf(stderr, "IMG_Init(): %s\n", SDL_GetError());
        return false;
    }*/
    SDL_CreateWindowAndRenderer(800, 480, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    return true;
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

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    // snake_render(&snake_1);
    SDL_RenderPresent(renderer);
}

void update() {
    snake_move(&snake_1);
}

void close() {
    if(window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}