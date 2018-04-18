#include "snake.h"
#include "../../standard/math/point.h"

const short int TILE_SIZE = 16;

void snake_grow(snake_t *snake) {
    assert(snake);
    point_t elem = *(point_t*)queue_front(&snake->body);
    elem = point_add(elem, snake->direction);
    queue_insert_at(&snake->body, &elem, 0);
    ++snake->lenght;
    // je serais d'avis d'ajouter le nouveau en bout de file en vrai a voir ce qui est plus facile

}

void snake_diminish(snake_t *snake){
    queue_erase_at(&snake->body, snake->lenght);
    --snake->lenght;
}

void change_dir(point_t *last_dir, char new_dir) {//note, certaines situations ne sont pas prises en compte, c'est normale hors des cas ci-dessous le serpent doit garder sa trajectoire précèdente
    if(new_dir == 'G' && last_dir->x <= 0 && last_dir->x > -36){//on part du principe que les directions sont modélisées par un cercle de 36 pixels de rayon
        last_dir->x -= 2;//le serpent doit à chaque tic se déplacer de 36 pixels en valeur absolue
        if(last_dir->y < 0){
            last_dir->y += 2;
        }else{
            last_dir->y -= 2;
        }
    }
    if(new_dir == 'D' && last_dir->x >= 0 && last_dir->x < 36){
        last_dir->x += 2;
        if(last_dir->y < 0){
            last_dir->y += 2;
        }else{
            last_dir->y -= 2;
        }
    }
    if(new_dir == 'H' && last_dir->y <= 0 && last_dir->y > -36){
        last_dir->y -= 2;
        if(last_dir->x < 0){
            last_dir->x += 2;
        }else{
            last_dir->x -= 2;
        }
    }
    if(new_dir == 'B' && last_dir->y >= 0 && last_dir->y < 36){
        last_dir->y += 2;
        if(last_dir->x < 0){
            last_dir->x += 2;
        }else{
            last_dir->x -= 2;
        }
    }
}


void snake_move(snake_t *snake){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    SDL_PumpEvents();
    if (state[SDL_SCANCODE_UP]) {
        change_dir(&snake->direction, 'H');
    } else if (state[SDL_SCANCODE_DOWN]) {
        change_dir(&snake->direction, 'B');
    } else if (state[SDL_SCANCODE_LEFT]) {
        change_dir(&snake->direction, 'G');
    } else if (state[SDL_SCANCODE_RIGHT]) {
        change_dir(&snake->direction, 'D');
    } else if (state[SDL_SCANCODE_ESCAPE]) {
        exit(0);
    }
    snake_diminish(snake);
    snake_grow(snake);
}

void snake_draw(const snake_t *snake);