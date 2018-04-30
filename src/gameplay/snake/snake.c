#include "snake.h"
#include "../../standard/math/point.h"

#define MAX_X 800
#define MAX_Y 480

SDL_Texture* snake_texture;

void snake_init(snake_t *snake){
    point_t point;
    point.x = 0;
    point.y = 0;
    while(snake->lenght > 0){
        snake_diminish(snake);
    }
    snake->direction = point;
    snake_grow(snake);//on donne une tête a notre serpant
}

void snake_grow(snake_t *snake) {
    assert(snake);
    point_t elem = *(point_t*)list_front(&snake->body);
    elem = point_add(elem, snake->direction);
    list_push_front(&snake->body, &elem);
    ++snake->lenght;
}

void snake_diminish(snake_t *snake){
    list_pop_back(&snake->body);
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
    if (last_dir->x < 0){//si on passe à travers l'un des bords de la map on apparait de l'autre cote
        last_dir->x += MAX_X;
    }
    if (last_dir->x > MAX_X){//si on passe à travers l'un des bords de la map on apparait de l'autre cote
        last_dir->x -= 0;
    }
    if (last_dir->y < 0){//si on passe à travers l'un des bords de la map on apparait de l'autre cote
        last_dir->y += MAX_Y;
    }
    if (last_dir->y > MAX_Y){//si on passe à travers l'un des bords de la map on apparait de l'autre cote
        last_dir->y -= 0;
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

void snake_load_texture() {
    snake_texture = load_texture("../res/snake/snake.png");
}

void snake_render_body(void* element) {
    snake_body_t *body = element;
    SDL_Rect src;
    switch (body->type) {
        case HEAD:
            src = (SDL_Rect){0, 0, 50, 50};
            break;
        case BODY:
            src = (SDL_Rect){50, 0, 50, 50};
            break;
        case TAIL:
            src = (SDL_Rect){100, 0, 50, 50};
            break;
    }
    SDL_Rect dst = {body->position->x, body->position->y, 16, 16}; //deux dernier chiffres = taille texture
    double angle = 0; // comment faire :x TODO
    if(!SDL_RenderCopyEx(get_renderer(), snake_texture, &src, &dst, angle, NULL, SDL_FLIP_NONE))
        fprintf(stderr, "SDL_RenderCopyEx(): %s\n", SDL_GetError());
}

void snake_render(snake_t *snake) {
    assert(snake);
    for_each(&snake->body, &snake_render_body);
}