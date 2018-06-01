//
// Created by user on 23/05/2018.
//
#include "element.h"

void init_apple(element_t *element, const point_t* position){
    element->position = *position;
    element->type = ELEMENT_APPLE;
    element->element_effect = &element_effect_apple;
    element->element_render = &element_render_apple;
}

void init_bombe(element_t *element, const point_t* position){
    element->position = *position;
    element->type = ELEMENT_BOMBE;
    element->element_effect = &element_effect_bombe;
    element->element_render = &element_render_bombe;
}

void init_wall(element_t *element, const point_t* position){
    element->position = *position;
    element->type = ELEMENT_WALL;
    element->element_effect = &element_effect_wall;
    element->element_render = &element_render_wall;
}

void element_init(element_t *element, const point_t* position, int type) {
    assert(element);
    if(type == ELEMENT_APPLE)
        init_apple(element, position);
    else if (type == ELEMENT_BOMBE)
        init_bombe(element, position);
    else if(type == ELEMENT_WALL)
        init_wall(element, position);
}

element_t *element_create(const point_t* position, int type) {
    element_t *element = calloc(1, sizeof(element_t));
    if (!element) {
        perror("calloc():");
        return NULL;
    }
    element_init(element, position, type);
    return element;
}

void element_render_apple(SDL_Renderer* renderer) {
    //TODO
}

void element_render_bombe(SDL_Renderer* renderer) {
    //TODO
}

void element_render_wall(SDL_Renderer* renderer) {
    //TODO
}


bool collision(snake_t *snake, element_t *element){ /* Retourne vrai si la collision a lieu */
    assert(snake && element);
    snake_t *snake_1 = (snake_t *)snake;
    point_t *point = (point_t *)&snake_head(snake_1)->position;
    if(point_distance(point, &element->position) < 32){
        element->element_effect(snake);
        return true;
    }
    return false;
}

void element_effect_apple(element_t *element, snake_t *snake) {
    assert(element && snake);
    if(collision(snake, element)){
        snake_grow(snake);
    }
}

void element_effect_bombe(element_t *element, snake_t *snake) {
    assert(element && snake);
    snake_diminish(snake);
}

void element_effect_wall(element_t *element, snake_t *snake) {
    assert(element && snake);
    while(snake->lenght < 0){
        snake_diminish(snake);
    }
}




