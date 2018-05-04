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
    bool end = false;
    if (!init()) return -1;
    if(!snake_load_texture()) return -1;

    snake_init(&snake_1, 3, NULL);
    printf("%p", renderer);
    SDL_Event event;
    while (!end) {
        SDL_WaitEvent(&event);
        end = event.window.event == SDL_WINDOWEVENT_CLOSE;
        update();
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
    /*if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        fprintf(stderr, "IMG_Init(): %s\n", SDL_GetError());
        return false;
    }*/
    window = SDL_CreateWindow("Test SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow(): %s\n", SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer(): %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
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
    SDL_SetRenderDrawColor(renderer, 15, 78, 234, 255);
    snake_render(&snake_1);
    SDL_RenderPresent(renderer);
}

void update() {
    snake_move(&snake_1);
}

void close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Renderer *get_renderer() {
    return renderer;
}