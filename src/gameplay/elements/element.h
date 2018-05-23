//
// Created by user on 23/05/2018.
//

#ifndef SNAKE_IO_ELEMENT_H
#define SNAKE_IO_ELEMENT_H

#include "../../standard/math/point.h"
#include "../snake/snake.h"

typedef struct element {
    point_t position;
    void (*element_effet)(void *);
    void (*element_render)(void);
}element_t;

void init_bombe(element_t *element, point_t position);
void init_mur(element_t *element, point_t position);
void init_pomme(element_t *element, point_t position);

void  effet_bombe(void *snake);
void effet_mur(void *snake);
void effet_pomme(void *snake);


void render_bombe(void);
void render_mur(void);
void render_pomme(void);


#endif //SNAKE_IO_ELEMENT_H
