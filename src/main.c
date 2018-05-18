#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include <SDL.h>
#include <SDL_timer.h>
#include <time.h>

#include "input.h"
#include "gameplay/snake/snake.h"

#define TICKS 33

SDL_Window* window;
SDL_Renderer* renderer;

snake_t snake_p1, snake_p2;

bool init();
void render();
void update();
void close_();

int main(int argc, char *argv[]) {
    bool end = false;
    if (!init()) return -1;
    if(!snake_load_texture()) return -1;
    point_t start = {25, 25};
    snake_init(&snake_p1, 3, &start, 0);
    SDL_Event event;
    unsigned int start_time, end_time;
    while (!end) {
        start_time = SDL_GetTicks();
        SDL_PollEvent(&event);
        end = event.window.event == SDL_WINDOWEVENT_CLOSE;
        input();
        update();
        render();
        end_time = SDL_GetTicks();
        if(end_time - start_time < 33)
            SDL_Delay(33 - end_time + start_time);
    }
    close_();
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

void render() {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 15, 78, 234, 255);
    snake_render(&snake_p1);
    SDL_RenderPresent(renderer);
}

void update() {
    snake_move(&snake_p1);
}

void close_() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Renderer *get_renderer() {
    return renderer;
}

snake_t *get_player1() {
    return &snake_p1;
}

snake_t *get_player2() {
    return &snake_p2;
}