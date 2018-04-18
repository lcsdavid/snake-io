#include "snake.h"
#include "../../standard/math/point.h"

SDL_Texture* snake_texture;

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



/* SDL */

void snake_load_texture(snake_t *snake, SDL_Renderer *renderer, const char *file) {
    // TODO
}

void snake_render_body(void* element) {
    snake_body_t *body = element;
    SDL_Rect src;
    switch (body->type) {
        case HEAD:
            src = {};
            break;
        case BODY:
            src = {};
            break;
        case TAIL:
            src = {};
            break;
    }
    SDL_Rect dst = {body->position->x, body->position->y, 16, 16}; //deux dernier chiffres = taille texture
    double angle = 0;
    if(!SDL_RenderCopyEx(get_renderer(), snake_texture, &src, &dst, angle, NULL, SDL_FLIP_NONE))
        fprintf(stderr, "SDL_RenderCopyEx(): %s\n", SDL_GetError());
}

void snake_render(const snake_t *snake) {
    assert(snake);
    for_each(&snake->body, &snake_render_body);
}