#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <time.h>

#include "gameplay/snake/snake.h"

typedef struct {
    snake_t player_one;
    snake_t player_two;
} gamestate_t;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool end;
    gamestate_t gamestate;
} appstate_t;

bool init(appstate_t *appstate);
void close(appstate_t *appstate);
void loop(appstate_t *appstate);
void input(appstate_t *appstate);
void update(gamestate_t *gamestate);
void render(appstate_t *appstate);

int main(int argc, char *argv[]) {
    appstate_t appstate;
    if (!init(&appstate))
        return EXIT_FAILURE;
    point_t start = {50, 50};
    snake_init(&appstate.gamestate.player_one, 3, &start, 0);
    unsigned int start_time, end_time;
    while (!appstate.end) {
        start_time = SDL_GetTicks();
        loop(&appstate);
        end_time = SDL_GetTicks();
        if(end_time - start_time < 16)
            SDL_Delay(16 - end_time + start_time);
    }
    close(&appstate);
    return 0;
}

bool init(appstate_t *appstate) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init(): %s\n", SDL_GetError());
        return false;
    }
    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init(): %s\n", SDL_GetError());
        return false;
    }
    SDL_Window *window = SDL_CreateWindow("Test SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow(): %s\n", SDL_GetError());
        return false;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer(): %s\n", SDL_GetError());
        return false;
    }
    appstate->window = window;
    appstate->renderer = renderer;
    appstate->end = false;

    if(!snake_load_texture(appstate->renderer))
        return false;
    return true;
}

void loop(appstate_t *appstate) {
    input(appstate);
    update(&appstate->gamestate);
    render(appstate);
}

void input(appstate_t *appstate) {
    SDL_Event event;
    if(SDL_PollEvent(&event))
        switch(event.type) {
            case SDL_WINDOWEVENT_CLOSE:
                appstate->end = true;
                break;
            case SDL_QUIT:
                appstate->end = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        appstate->end = true;
                        break;
                    case SDLK_LEFT:
                        snake_change_direction(&appstate->gamestate.player_one, true);
                        break;
                    case SDLK_RIGHT:
                        snake_change_direction(&appstate->gamestate.player_one, false);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
}

void update(gamestate_t *gamestate) {
    snake_move(&gamestate->player_one);
}

void render(appstate_t *appstate) {
    SDL_RenderClear(appstate->renderer);
    SDL_SetRenderDrawColor(appstate->renderer, 15, 78, 234, 255);
    snake_render(&appstate->gamestate.player_one, appstate->renderer);
    SDL_RenderPresent(appstate->renderer);
}

void close(appstate_t *appstate) {
    SDL_DestroyRenderer(appstate->renderer);
    SDL_DestroyWindow(appstate->window);
    SDL_Quit();
}