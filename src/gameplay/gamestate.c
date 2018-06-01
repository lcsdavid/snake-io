#include "gamestate.h"

#include "elements/element.h"

#include "../standard/collection/list_iterator.h"

void gamestate_init(gamestate_t *gamestate) {
    point_t start = {10, 10};
    snake_init(&gamestate->player_one, &start, 0);
    list_init(&gamestate->elements);
    gamestate->multiplayer = false;
    gamestate->fullscreen = false;
    point_t point = new_point(gamestate);
    list_push_front(&gamestate->elements, element_create(&point, ELEMENT_APPLE));
}

bool point_taken(const gamestate_t* gamestate, const point_t* point) {
    iterator_t *it = NULL;

    for(int s = 0; s < 1; s++) {
        if(s == 0)
            it = list_iterator_create(&gamestate->player_one.body);
        else if (s == 1)
            it = list_iterator_create(&gamestate->player_two.body);

        while (iterator_has_data(it)) {
            snake_node_t *current = iterator_data(it);
            if (point_distance(point, &current->position) < 64) /* Le point est déjà pris */
                return true;
            it = iterator_next(it);
        }
        iterator_destroy(it);
    }

    it = list_iterator_create(&gamestate->elements);
    while (iterator_has_data(it)) {//on vérifie ensuite que le point n'est pas situé sur un  autre élément
        element_t *current = iterator_data(it);
        if (point_distance(point, &current->position) < 32)
            return true;
    }
    return false;
}

point_t new_point(const gamestate_t *gamestate) { /* Indique un point disponible pour placer un element */
    point_t point;
    do {
        point_init(&point, rand(), rand());
    } while(point_taken(gamestate, &point));
    return point;
}