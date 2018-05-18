#include "snake.h"

#define MAX_X 800
#define MAX_Y 480

SDL_Texture *snake_texture;

//

snake_node_t *snake_node_create(const point_t *point, double angle) {
    snake_node_t *snake_node = calloc(1, sizeof(snake_node_t));
    if (!snake_node) {
        perror("calloc():");
        return NULL;
    }
    snake_node->position = *point;
    snake_node->angle = angle;
    return snake_node;
}

//
void snake_init(snake_t *snake, size_t size, const point_t *position, double direction) {
    assert(snake && position);
    list_init(&snake->body, snake_node_create(position, direction));
    snake->lenght = 1;
    for (size_t i = 0; i < size - 1; i++)
        snake_grow(snake);
}

//

snake_node_t *snake_head(const snake_t *snake) {
    assert(snake);
    return list_front(&snake->body);
}

snake_node_t *snake_tail(const snake_t *snake) {
    assert(snake);
    return list_back(&snake->body);
}

//

void snake_grow(snake_t *snake) {
    assert(snake && snake->lenght > 0);
    snake_node_t *snake_node = snake_node_create(&snake_head(snake)->position, snake_head(snake)->angle);
    list_push_front(&snake->body, snake_node);
    ++snake->lenght;
}

void snake_diminish(snake_t *snake) {
    assert(snake);
    if(snake->lenght > 0) {
        list_pop_back(&snake->body);
        --snake->lenght;
    }
}

//

double snake_change_direction(bool gauche, double angle) {
    if(gauche){
        angle += M_PI/36;
    }else{
        angle -= M_PI/36;
    }
    return angle;
}

void snake_move(snake_t *snake) {
    snake_head(snake)->position.x += (int)cos(-snake_head(snake)->angle);
    snake_head(snake)->position.y += (int)sin(snake_head(snake)->angle);
    //snake_change_direction(&snake->direction, direction);
    //for(size_t i = snake->lenght; i > 1; i--) {
    //    ((snake_node_t *)list_element_at(&snake->body, i))->position = ((snake_node_t *)list_element_at(&snake->body, i - 1))->position;
        //((snake_node_t *)list_element_at(&snake->body, i))->angle = ((snake_node_t *)list_element_at(&snake->body, i - 1))->angle;
    //}
    //snake_head(snake)->position = snake->direction;
    // /* Si on passe à travers l'un des bords de la map on apparait de l'autre cote. */
    if (snake_head(snake)->position.x < 0) snake_head(snake)->position.x += MAX_X;
    if (snake_head(snake)->position.x > MAX_X) snake_head(snake)->position.x -= 0;
    if (snake_head(snake)->position.y < 0) snake_head(snake)->position.y += MAX_Y;
    if (snake_head(snake)->position.y > MAX_Y) snake_head(snake)->position.y -= 0;
}

//

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
        if (point_distance(&head->position, &body_part->position) < 18)
            return true;
    }
    return false;
}

/* SDL */

bool snake_load_texture() {
    SDL_Surface *snake_surface = SDL_LoadBMP("../res/snake/snake.bmp");
    if (!snake_surface) {
        fprintf(stderr, "SDL_LoadBMP(): %s\n", SDL_GetError());
        return false;
    }
    snake_texture = SDL_CreateTextureFromSurface(get_renderer(), snake_surface);
    if (!snake_texture) {
        fprintf(stderr, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(snake_surface);
    return true;
}

void snake_render_body(void *element) {
    snake_node_t *node = element;
    if (!node)
        return;
    //SDL_Rect src = {node->position.x, node->position.y, 32, 32};
    SDL_Rect dst = {node->position.x, node->position.y, 32, 32}; //deux dernier chiffres = taille texture
    /*if(!SDL_RenderCopyEx(get_renderer(), snake_texture, &src, &dst, body->angle, NULL, SDL_FLIP_NONE))
        fprintf(stderr, "SDL_RenderCopyEx(): %s\n", SDL_GetError());*/
    SDL_RenderCopy(get_renderer(), snake_texture, NULL, &dst);
}

void snake_render(snake_t *snake) {
    assert(snake);
    for_each(&snake->body, &snake_render_body);
}

