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

#define FRAME_PER_SEC 60
#define TICKS_PER_SEC 30

typedef struct {
    snake_t player_one;
    snake_t player_two;
} gamestate_t;

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool end;
    gamestate_t gamestate;
    list_t elements;
    bool player2; //est a true s'il y a un deuxieme joueur, false sinon
} appstate_t;

bool point_taken(point_t point, appstate_t appstate);
point_t new_point(appstate_t appstate);
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
    snake_init(&appstate.gamestate.player_one, 1, &start, 0);
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



bool point_taken(point_t point, appstate_t appstate){
    snake_t snake1 = appstate.gamestate.player_one;
    snake_t snake2 = appstate.gamestate.player_two;
    iterator_t *it = list_iterator_create(&snake1.body);
    for(int i = 0; i < snake1.lenght; i++) {
        snake_node_t* current = iterator_data(it);
        if(point_distance(&point, &current->position) < 32){//le point est déjà pris
            return true;
        }
        it = iterator_next(it);
    }
    iterator_destroy(it);
    if(appstate.player2){
        iterator_t *it = list_iterator_create(&snake2.body);
        for(int i = 0; i < snake2.lenght; i++) {
            snake_node_t* current = iterator_data(it);
            if(point_distance(&point, &current->position) < 32){//le point est déjà pris
                return true;
            }
            it = iterator_next(it);
        }
        iterator_destroy(it);
    }
    iterator_t *iterator1 = list_iterator_create(&appstate.elements);
    for(int i =0; i < list_size(&appstate.elements); i++){//on vérifie ensuite que le point n'est pas situé sur un  autre élément
        element_t *current = iterator_data(it);
        if(point_distance(&point, &current->position) < 32){
            return true;
        }
    }
    return false;
}

point_t new_point(appstate_t appstate){ //indique un point disponible pour placer un element
    int a,b;
    point_t point;
    srand(time(NULL));
    a = rand();
    b = rand();
    point.x = a;
    point.y = b;
    while(point_taken(point, appstate)){
        a = rand();
        b = rand();
        point.x = a;
        point.y = b;
    }
    return point;
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
    appstate->player2 = false;

    //TODO regler les probelems d allocations
    point_t point = new_point(*appstate);
    element_t elem;
    init_pomme(&elem, point);
    node_t *node = node_create(NULL, NULL, &elem);

    appstate->elements.back = node;
    appstate->elements.front = node;
    //TODO initialiser les elements

    if(!snake_load_texture(appstate->renderer))
        return false;
    return true;
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
    for(int i = 0; i < list_size(&appstate->elements); i++){
        element_t *elem = list_element_at(&appstate->elements, i);
        collision(&appstate->gamestate.player_one, elem);
    }
}

void render(appstate_t *appstate) {
    SDL_RenderClear(appstate->renderer);
    SDL_SetRenderDrawColor(appstate->renderer, 15, 78, 234, 255);
    snake_render(&appstate->gamestate.player_one, appstate->renderer);
    SDL_RenderPresent(appstate->renderer);
    //TODO ajouter un deuxieme joueur
}

void close(appstate_t *appstate) {
    SDL_DestroyRenderer(appstate->renderer);
    SDL_DestroyWindow(appstate->window);
    SDL_Quit();
}