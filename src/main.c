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
                    case SDLK_g:
                        snake_grow(&appstate->gamestate.player_one);
                        break;
                    case SDLK_h:
                        snake_diminish(&appstate->gamestate.player_one);
                        break;
                    case SDLK_f:
                        if(appstate->gamestate.fullscreen == false){
                            appstate->gamestate.fullscreen = true;
                            SDL_SetWindowFullscreen(appstate->window, SDL_WINDOW_FULLSCREEN);
                        }else{
                            appstate->gamestate.fullscreen = false;
                            SDL_SetWindowFullscreen(appstate->window, 0);
                        }
                    default:
                        break;
                }
                break;
            default:
                break;
        }
}

void update(appstate_t *appstate) {
    snake_move(&appstate->gamestate.player_one);
    /*for(size_t i = 0; i < list_size(&appstate->gamestate.elements); i++){
        element_t *elem = list_element_at(&appstate->gamestate.elements, i);
        collision(&appstate->gamestate.player_one, elem);
    }*/
}

void render(appstate_t *appstate) {
    SDL_RenderClear(appstate->renderer);
    SDL_SetRenderDrawColor(appstate->renderer, 15, 78, 234, 255);
    snake_render(&appstate->gamestate.player_one, appstate->renderer);
    SDL_RenderPresent(appstate->renderer);
    //TODO ajouter un deuxieme joueur et les différents éléments
}

void close(appstate_t *appstate) {
    SDL_DestroyRenderer(appstate->renderer);
    SDL_DestroyWindow(appstate->window);
    SDL_Quit();
}