#include "gamestate.h"

#include "elements/element.h"

#include "../standard/collection/list_iterator.h"
#include "../standard/collection/node.h"
#include "../standard/math/point.h"

void gamestate_init(gamestate_t *gamestate) {
    point_t start = {10, 10};
    gamestate->pommes = 0;
    snake_init(&gamestate->player_one, &start, 0);
    list_init(&gamestate->elements);
    gamestate->multiplayer = false;
    gamestate->fullscreen = false;
    point_t point = new_point(gamestate);
    list_push_front(&gamestate->elements, element_create(&point, ELEMENT_APPLE));
}

void gamestate_render(gamestate_t *gamestate, SDL_Renderer *renderer) {
    snake_render(&gamestate->player_one, renderer);

    iterator_t *it = list_iterator_create(&gamestate->elements, START_FRONT);
    while (iterator_has_data(it)) {
        element_t *element = iterator_data(it);
        element_render(element, renderer);
        it = iterator_next(it);
    }
    iterator_destroy(it);
}

bool gestion_collision(gamestate_t *gamestate, element_t *element){
    if(element->type == 1){//si c'est une pomme

        element->element_effect(&gamestate->player_one);
        gamestate->pommes += 1;
        element->position = new_point(gamestate);
        //mettre l'apparition d'obstacles
    }else{
        if(gamestate->player_one.lenght <= 1){
            return false;
        }

        element->element_effect(&gamestate->player_one);
        element->position.y += 800;
        element->position.x += 800;
    }
    if(gamestate->pommes%3 == 1){//toutes les trois pommes on fait apparaitre une bombe
        point_t point = new_point(gamestate);
        list_push_front(&gamestate->elements, element_create(&point, ELEMENT_BOMBE));
    }
    return true;
}



bool collision(gamestate_t *gamestate) {
    assert(gamestate);
    float distance; // floattant pour mesurer la distance
    point_t *po = (point_t *)gamestate->player_one.body.front->data;
    for(int s = 0; s < 1; s++) {
        int i = 0;//on va s'en servir pour compter le rang des éléments
        iterator_t *it = list_iterator_create(&gamestate->elements, START_FRONT);
        while (iterator_has_data(it)) {
            element_t *element = iterator_data(it);
            if(element != po){ //si on a bien affaire a deux points différents
                point_t point = element->position;
                point.x += 16;
                point.y += 16; //les coordonnées originelles d'un element désignent le coin en haut a gauche de sa tuile, avec cette opération on obtient le centre de la tuile (qui fait 16*16)
                distance = point_distance(&point, po);
                if(distance <= 32){
                    if(!gestion_collision(gamestate, element)){
                        return true;
                    }

                }
            }
            it = iterator_next(it);
            i++;
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
        point_init(&point, rand() % 800, rand() % 600);
        compteur++;
    } while(point_taken(gamestate, &point) && compteur < 50);
    return point;
}