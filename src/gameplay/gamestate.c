#include "gamestate.h"

#include "elements/element.h"

#include "../standard/collection/list_iterator.h"
#include "../standard/collection/node.h"
#include "../standard/math/point.h"

static void collision_bis(gamestate_t*, snake_t*);

void gamestate_init(gamestate_t *gamestate) {
    point_t start = {10, 10};
    gamestate->difficulte = 0;
    gamestate->modeArcade = false;
    snake_init(&gamestate->player_one, &start, 0);
    list_init(&gamestate->elements);
    gamestate->multiplayer = false;
    point_t point = new_point(gamestate);
    list_push_front(&gamestate->elements, element_create(&point, ELEMENT_APPLE));
    point = new_point(gamestate);
    point.x = 1250;
    element_create(&point, ELEMENT_LASER);
    gamestate->laser1 = element_create(&point, ELEMENT_LASER);
    point = new_point(gamestate);
    point.x = 1350;
    element_create(&point, ELEMENT_LASER);
    gamestate->laser2 = element_create(&point, ELEMENT_LASER);
    gamestate->angle_laser1 = 0;
    gamestate->angle_laser2 = 0;
    list_push_front(&gamestate->elements, gamestate->laser1);
    list_push_front(&gamestate->elements, gamestate->laser2);
}

bool gamestate_update(gamestate_t *gamestate) {
    if (gamestate->player_one.lenght < 1)
        return false;
    if (gamestate->multiplayer)
        if (gamestate->player_two.lenght < 1)
            return false;

    snake_move(&gamestate->player_one);
    if (gamestate->multiplayer)
        snake_move(&gamestate->player_two);

    collision_bis(gamestate, &gamestate->player_one);
    if (gamestate->multiplayer)
        collision_bis(gamestate, &gamestate->player_two);
    return true;
}

/* Render */

void gamestate_render(gamestate_t *gamestate, SDL_Renderer *renderer) {
    iterator_t *it = list_iterator_create(&gamestate->elements, START_FRONT);
    while (iterator_has_data(it)) {
        element_t *element = iterator_data(it);
        element_render(element, renderer);
        it = iterator_next(it);
    }
    iterator_destroy(it);

    snake_render(&gamestate->player_one, renderer, false);
    if (gamestate->multiplayer)
        snake_render(&gamestate->player_two, renderer, true);


}

static void collision_bis(gamestate_t *gamestate, snake_t *snake) {
    assert(gamestate);
    snake_self_eating(snake);
    element_t *element = NULL;
    for (size_t i = 0; i < gamestate->elements.size; i++) {
        element = list_element_at(&gamestate->elements, i);
        SDL_Log("%lld %d %lf %lf", i, element->type, element->position.x, element->position.y);
        if(point_distance(&snake_head(snake)->position, &element->position) < 32) {
            element_effect(element, snake);
            if(element->type == ELEMENT_APPLE) {
                point_t point = new_point(gamestate);
                list_push_back(&gamestate->elements, element_create(&point, ELEMENT_APPLE));
            } else if(element->type == ELEMENT_BOMBE)
                element->position = new_point(gamestate);
            list_erase_at(&gamestate->elements, i);
            i--;
            gamestate->difficulte += 1;
            // Toutes les trois difficulte on fait apparaitre une bombe
            if (gamestate->difficulte % 3 == 0) {
                point_t point = new_point(gamestate);
                list_push_front(&gamestate->elements, element_create(&point, ELEMENT_BOMBE));
            }
            // Tous les 7 éléments un mur apparait
            if (gamestate->difficulte % 7 == 0) {
                point_t point = new_point(gamestate);
                list_push_front(&gamestate->elements, element_create(&point, ELEMENT_WALL));
            }
        }
    }
}

bool collision(gamestate_t *gamestate) {
    assert(gamestate);
    double distance; // floattant pour mesurer la distance
    point_t *po = (point_t *) gamestate->player_one.body.front->data;
    snake_t *snake = &gamestate->player_one;
    collision_bis(gamestate, &gamestate->player_one);
    if (gamestate->multiplayer)
        collision_bis(gamestate, &gamestate->player_two);
    int i = 0;
    for (int s = 0; s < 2; s++) {
        iterator_t *it = list_iterator_create(&gamestate->elements, START_FRONT);
        double angle = 0;
        if (s == 0) {
            po = &gamestate->laser1->position;
            angle = gamestate->angle_laser1;
        }
        if (s == 1) {
            po = &gamestate->laser2->position;
            angle = gamestate->angle_laser2;
        }

        po->x += SNAKE_BODY_DIAMETER * 2 * cos(angle);
        po->y += SNAKE_BODY_DIAMETER * 2 * sin(angle);
        while (iterator_has_data(it)) {
            element_t *element = iterator_data(it);
            point_t point = element->position;
            point.x += 16;
            point.y += 16; //les coordonnées originelles d'un element désignent le coin en haut a gauche de sa tuile, avec cette opération on obtient le centre de la tuile (qui fait 16*16)
            distance = point_distance(&point, po);
            if (&point != po && distance <= 64) {
                //list_erase_at(&gamestate->elements, i);
                po->x += 1250;
            }
            i++;
            iterator_next(it);
        }
        iterator_destroy(it);

    }
    return false;
}

bool point_taken(const gamestate_t *gamestate, const point_t *point) {
    iterator_t *it = NULL;

    for (int s = 0; s < 1; s++) {
        if (s == 0)
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
        if (point_distance(point, &current->position) < 32) {
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
    } while (point_taken(gamestate, &point) && compteur < 77);
    return point;
}
