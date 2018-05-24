//
// Created by user on 23/05/2018.
//
#include "element.h"


void init_bombe(element_t *element, point_t position){
    element->element_effet = effet_bombe;
    element->position = position;
    element->element_render = render_bombe;
    element->type = 2;
}
void init_mur(element_t *element, point_t position){
    element->element_effet = effet_mur;
    element->position = position;
    element->element_render = render_mur;
    element->type = 3;
}

void init_pomme(element_t *element, point_t position){
    element->element_effet = &effet_pomme;
    element->position = position;
    element->element_render = &render_pomme;
    element->type = 1;
}


void render_bombe(void){
    //TODO
}

void render_mur(void){
    //TODO
}

void render_pomme(void){
    //TODO
}

bool collision(void *snake, element_t *elem){//retourne vraie si la collision a lieu
    snake_t *snake_1 = (snake_t *)snake;
    point_t *point = (point_t *)snake_1->body.front->data;
    if(point_distance(point, &elem->position) < 32){
        elem->element_effet(snake);
        return true;
    }
    return false;
}

void effet_bombe(void *snake){
    snake_t *snake_1 = (snake_t *)snake;
    snake_diminish(snake_1);
}

void effet_mur(void *snake){
    snake_t *snake_1 = (snake_t *)snake;
    while(snake_1->lenght < 0){
        snake_diminish(snake_1);
    }
}

void effet_pomme(void *snake){
    snake_t *snake_1 = (snake_t *)snake;
    snake_grow(snake_1);
}