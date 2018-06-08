#include "gamestate.h"

#include "elements/element.h"

#include "../standard/collection/list_iterator.h"
#include "../standard/collection/node.h"
#include "../standard/math/point.h"

void gamestate_init(gamestate_t *gamestate) {
    point_t start = {10, 10};
    gamestate->difficulte = 0;
    snake_init(&gamestate->player_one, &start, 0);
    list_init(&gamestate->elements);
    gamestate->multiplayer = false;
    point_t point = new_point(gamestate);
    list_push_front(&gamestate->elements, element_create(&point, ELEMENT_APPLE));
}

void gamestate_render(gamestate_t *gamestate, SDL_Renderer *renderer) {
    snake_render(&gamestate->player_one, renderer, false);
    if(gamestate->multiplayer)
        snake_render(&gamestate->player_two, renderer, true);

    iterator_t *it = list_iterator_create(&gamestate->elements, START_FRONT);
    while (iterator_has_data(it)) {
        element_t *element = iterator_data(it);
        element->element_render(element, renderer);
        it = iterator_next(it);
    }
    iterator_destroy(it);
}

bool gestion_collision(gamestate_t *gamestate, element_t *element, snake_t *snake){
    gamestate->difficulte += 1;
    if(element->type == 1){//si c'est une pomme
        element->element_effect(snake);
        element->position = new_point(gamestate);
        //mettre l'apparition d'obstacles
    }else if(element->type == 2){
        if(snake->lenght <= 1){//mort du joueur
            return false;
        }
        element->element_effect(snake);
        element->position = new_point(gamestate);
    }else if(element->type == 3){
        return false;
    }
    if(gamestate->difficulte%3 == 0){//toutes les trois difficulte on fait apparaitre une bombe
        point_t point = new_point(gamestate);
        list_push_front(&gamestate->elements, element_create(&point, ELEMENT_BOMBE));
    }
    if(gamestate->difficulte%7 == 0){///tous les 7 éléments un mur apparait
        point_t point = new_point(gamestate);
        list_push_front(&gamestate->elements, element_create(&point, ELEMENT_WALL));

    }
    return true;
}



bool collision(gamestate_t *gamestate) {
    assert(gamestate);
    double distance; // floattant pour mesurer la distance
    point_t *po = (point_t *)gamestate->player_one.body.front->data;
    snake_t *snake = &gamestate->player_one;
    int limite = 1;
    if(gamestate->multiplayer)//on stock le nombre de serpents que l'on doit parcourird
        limite = 2;
    for(int s = 0; s < limite; s++) {
        if(s == 1){
            po = (point_t *)gamestate->player_two.body.front->data;
            snake = &gamestate->player_two;
        }
        iterator_t *it = list_iterator_create(&gamestate->elements, START_FRONT);
        while (iterator_has_data(it)) {
            element_t *element = iterator_data(it);
            if(&element->position != po){ //si on a bien affaire a deux points différents
                point_t point = element->position;
                point.x += 16;
                point.y += 16; //les coordonnées originelles d'un element désignent le coin en haut a gauche de sa tuile, avec cette opération on obtient le centre de la tuile (qui fait 16*16)
                distance = point_distance(&point, po);
                if(distance <= 32){
                    if(!gestion_collision(gamestate, element, snake)){
                        return true;
                    }
                    list_erase_at(&gamestate->elements, i);
                }
            }
            i++;
            it = iterator_next(it);
        }
    }
    return  false;
}

bool point_taken(const gamestate_t* gamestate, const point_t* point) {
    iterator_t *it = NULL;

    for(int s = 0; s < 1; s++) {
        if(s == 0)
            it = list_iterator_create(&gamestate->player_one.body, START_FRONT);
        else if (s == 1)
            it = list_iterator_create(&gamestate->player_two.body, START_FRONT);

        while (iterator_has_data(it)) {
            snake_node_t *current = iterator_data(it);
            if (point_distance(point, &current->position) < 64) /* Le point est déjà pris */
                return true;
            it = iterator_next(it);
        }
        iterator_destroy(it);
    }

    it = list_iterator_create(&gamestate->elements, START_FRONT);
    while (iterator_has_data(it)) {//on vérifie ensuite que le point n'est pas situé sur un  autre élément
        element_t *current = iterator_data(it);
        if (point_distance(point, &current->position) < 32){
            iterator_destroy(it);
            return true;
        }
        it = iterator_next(it);
    }

    return false;
}

point_t new_point(const gamestate_t *gamestate) { /* Indique un point disponible pour placer un element */
    point_t point;
    int compteur = 0;
    do {
        point_init(&point, rand() % 1150, rand() % 750);
        compteur++;
    } while(point_taken(gamestate, &point) && compteur < 77);
    return point;
}
