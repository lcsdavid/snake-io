#include "snake.h"
#include "../../standard/math/point.h"

#define MAX_X 800
#define MAX_Y 480

SDL_Texture *snake_texture;

void snake_init(snake_t *snake, size_t size, point_t *direction) {
    assert(snake);
    snake->body.front = NULL;
    snake->body.back = NULL;
    snake->lenght = 0;
    if (direction) snake->direction = *direction;
    else snake->direction = (point_t){0, 0};
    for (size_t i = 0; i < size; i++)
        snake_grow(snake);
}

snake_node_t *snake_head(const snake_t *snake) {
    assert(snake);
    return list_front(&snake->body);
}

snake_node_t *snake_tail(const snake_t *snake) {
    assert(snake);
    return list_back(&snake->body);
}

void snake_grow(snake_t *snake) {
    assert(snake);
    point_t elem;
    if (list_empty(&snake->body)) {
        elem.x = 0;
        elem.y = 0;
    } else {
        elem = *(point_t *) list_front(&snake->body);
        elem = point_add(elem, snake->direction);
    }
    list_push_front(&snake->body, &elem);
    ++snake->lenght;
}

void snake_diminish(snake_t *snake) {
    list_pop_back(&snake->body);
    --snake->lenght;
}

void change_dir(point_t *last_dir, char new_dir) {//note, certaines situations ne sont pas prises en compte, c'est normale hors des cas ci-dessous le serpent doit garder sa trajectoire précèdente
    if (new_dir == 'G' && last_dir->x <= 0 &&
        last_dir->x > -36) {//on part du principe que les directions sont modélisées par un cercle de 36 pixels de rayon
        last_dir->x -= 2;//le serpent doit à chaque tic se déplacer de 36 pixels en valeur absolue
        if (last_dir->y < 0) {
            last_dir->y += 2;
        } else {
            last_dir->y -= 2;
        }
    }
    if (new_dir == 'D' && last_dir->x >= 0 && last_dir->x < 36) {
        last_dir->x += 2;
        if (last_dir->y < 0) {
            last_dir->y += 2;
        } else {
            last_dir->y -= 2;
        }
    }
    if (new_dir == 'H' && last_dir->y <= 0 && last_dir->y > -36) {
        last_dir->y -= 2;
        if (last_dir->x < 0) {
            last_dir->x += 2;
        } else {
            last_dir->x -= 2;
        }
    }
    if (new_dir == 'B' && last_dir->y >= 0 && last_dir->y < 36) {
        last_dir->y += 2;
        if (last_dir->x < 0) {
            last_dir->x += 2;
        } else {
            last_dir->x -= 2;
        }
    }
    if (last_dir->x < 0) {//si on passe à travers l'un des bords de la map on apparait de l'autre cote
        last_dir->x += MAX_X;
    }
    if (last_dir->x > MAX_X) {//si on passe à travers l'un des bords de la map on apparait de l'autre cote
        last_dir->x -= 0;
    }
    if (last_dir->y < 0) {//si on passe à travers l'un des bords de la map on apparait de l'autre cote
        last_dir->y += MAX_Y;
    }
    if (last_dir->y > MAX_Y) {//si on passe à travers l'un des bords de la map on apparait de l'autre cote
        last_dir->y -= 0;
    }
}

void snake_move(snake_t *snake) {
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

bool snake_is_head(const snake_t *snake, const snake_node_t *node) {
    assert(snake && node);
    return snake_head(snake) == node;
}

bool snake_is_tail(const snake_t *snake, const snake_node_t *node) {
    assert(snake && node);
    return snake_tail(snake) == node;
}

bool snake_collision(snake_t *snake, point_t *point) {
    if (snake_self_eating(snake)) {
        return true;
    }
    //TODO ajouter les différents éléments (missiles, mur, pièges, deuxieme joueur ...
    return false;
}

bool snake_self_eating(snake_t *snake) {
    assert(snake);
    snake_node_t *head = snake_head(snake);
    snake_node_t *body_part;
    for (size_t i = 1; i < snake->lenght; i++) {
        body_part = list_element_at(&snake->body, i);
        if (point_distance(head->position, body_part->position) < 18)
            return true;
    }
    return false;
}

/* SDL */

bool snake_load_texture() {
    // snake_texture = load_texture("../res/snake/snake.png");
    /*SDL_Surface*  field_surface = NULL;
    SDL_Surface*  fruit_surface = NULL;
    SDL_Surface*  shead_surface = NULL;
    SDL_Surface*  snake_surface = NULL;
    SDL_Texture*  field_texture = NULL;
    SDL_Texture*  fruit_texture = NULL;
    SDL_Texture*  shead_texture = NULL;
    SDL_Texture*  snake_texture = NULL;*/
    //fruit_surface = SDL_LoadBMP("C:\\Users\\user\\Documents\\GitHub\\snake-io\\res\\snake\\apple.bmp");
    //shead_surface = SDL_LoadBMP("C:\\Users\\user\\Documents\\GitHub\\snake-io\\res\\snake\\head.bmp");
   SDL_Surface *snake_surface = SDL_LoadBMP("../res/snake/snake.bmp");
    //field_surface = SDL_LoadBMP("C:\\Users\\user\\Documents\\GitHub\\snake-io\\res\\snake\\field.bmp");
    if(!snake_surface) {
        fprintf(stderr, "SDL_LoadBMP(): %s\n", SDL_GetError());
        return false;
    }
    snake_texture = SDL_CreateTextureFromSurface(get_renderer(), snake_surface);
    /*fruit_texture = SDL_CreateTextureFromSurface(get_renderer(), fruit_surface);
    shead_texture = SDL_CreateTextureFromSurface(get_renderer(), shead_surface);
    field_texture = SDL_CreateTextureFromSurface(get_renderer(), field_surface);*/
    if(!snake_texture){
        fprintf(stderr, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void snake_render_body(void* element) {
    snake_node_t *node = element;
    //SDL_Rect src = {node->position.x, node->position.y, 32, 32};
    SDL_Rect dst = {255, 255, 64, 64}; //deux dernier chiffres = taille texture
    /*if(!SDL_RenderCopyEx(get_renderer(), snake_texture, &rect, &dst, body->angle, NULL, SDL_FLIP_NONE))
        fprintf(stderr, "SDL_RenderCopyEx(): %s\n", SDL_GetError());*/
    SDL_RenderCopy(get_renderer(), snake_texture, NULL, &dst);
}

void snake_render(snake_t *snake) {
    assert(snake);
    SDL_Rect dst = {255, 255, 64, 64};
    SDL_RenderCopy(get_renderer(), snake_texture, NULL, &dst);
    for_each(&snake->body, &snake_render_body);
}

