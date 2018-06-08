#include "snake.h"

#include "../../standard/collection/list_iterator.h"
#include "../../standard/math/point.h"

#define M_PI 3.14159265358979323846
#define MAX_X 1200
#define MAX_Y 800

SDL_Texture *snake_texture1;
SDL_Texture *snake_texture2;

//

void snake_node_init(snake_node_t *snake_node, const point_t *point, double angle) {
    assert(snake_node && point);
    snake_node->position = *point;
    snake_node->angle = angle;
}

snake_node_t *snake_node_create(const point_t *point, double angle) {
    snake_node_t *snake_node = calloc(1, sizeof(snake_node_t));
    if (!snake_node) {
        perror("calloc():");
        return NULL;
    }
    snake_node_init(snake_node, point, angle);
    return snake_node;
}

snake_node_t *snake_node_copy(const snake_node_t *snake_node) {
    assert(snake_node);
    return snake_node_create(&snake_node->position, snake_node->angle);
}

//
void snake_init(snake_t *snake, const point_t *position, double direction) {
    assert(snake && position);
    list_init(&snake->body);
    list_push_back(&snake->body, snake_node_create(position, direction));
    snake->lenght = 1;
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
    snake_node_t *tail = snake_tail(snake);
    point_t pos = {tail->position.x - cos(tail->angle) * SNAKE_BODY_DIAMETER,
                   tail->position.y - sin(tail->angle) * SNAKE_BODY_DIAMETER};
    list_push_back(&snake->body, snake_node_create(&pos, tail->angle));
    snake->lenght++;
}

void snake_diminish(snake_t *snake) {
    assert(snake);
    if (snake->lenght > 0) {
        list_pop_back(&snake->body);
        --snake->lenght;
    }
}

//

void snake_change_direction(snake_t *snake, bool gauche) {
    if (gauche)
        snake_head(snake)->angle -= M_PI / 100;
    else
        snake_head(snake)->angle += M_PI / 100;
}

bool snake_move(snake_t *snake) { // TODO améliorer la propagation la queue doit être vider plus efficacement
    snake_node_t *prev_node, *current_node;
    iterator_t *it = list_iterator_create(&snake->body, START_BACK);
    prev_node = iterator_data(it);
    it = iterator_previous(it);
    for (size_t i = 0; i < snake->lenght - 1; i++) {
        current_node = iterator_data(it);
        prev_node->position = current_node->position;
        prev_node->angle = current_node->angle;
        prev_node = current_node;
        it = iterator_previous(it);
    }
    prev_node->position.x += SNAKE_BODY_DIAMETER * cos(prev_node->angle);
    prev_node->position.y += SNAKE_BODY_DIAMETER * sin(prev_node->angle);

    /* Si on passe à travers l'un des bords de la map on apparait de l'autre cote. */
    if (snake_head(snake)->position.x < 0) snake_head(snake)->position.x = MAX_X;
    if (snake_head(snake)->position.x > MAX_X) snake_head(snake)->position.x = 0;
    if (snake_head(snake)->position.y < 0) snake_head(snake)->position.y = MAX_Y;
    if (snake_head(snake)->position.y > MAX_Y) snake_head(snake)->position.y = 0;

    if (snake_self_eating(snake)) {
        return false;
    }
    return true;
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
    iterator_t *it = list_iterator_create(&snake->body, START_FRONT);
    for(int i = 0; i < snake->lenght; i++) {
        snake_node_t* current = iterator_data(it);
        if(point_distance(point, &current->position) < 32) { /* Une partie du serpent rentre dans l'obstacle */
            return true;
        }
        it = iterator_next(it);
    }
    return false;
}

bool snake_self_eating(snake_t *snake) {
    assert(snake);
    snake_node_t *head = snake_head(snake);
    snake_node_t *body_part;
    for (size_t i = 2; i < snake->lenght; i++) {
        body_part = list_element_at(&snake->body, i);
        if (point_distance(&head->position, &body_part->position) < SNAKE_BODY_DIAMETER - 1){
            return true;

        }
    }
    return false;
}

/* SDL */

bool snake_load_texture(SDL_Renderer *renderer) {
    SDL_Surface *snake_surface = IMG_Load("../res/snake/snake1.png");
    if (!snake_surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP(): %s\n", SDL_GetError());
        return false;
    }
    snake_texture1 = SDL_CreateTextureFromSurface(renderer, snake_surface);
    if (!snake_texture1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        return false;
    }
    snake_surface = IMG_Load("../res/snake/snake.png");
    if (!snake_surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP(): %s\n", SDL_GetError());
        return false;
    }
    snake_texture2 = SDL_CreateTextureFromSurface(renderer, snake_surface);
    if (!snake_texture2) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(snake_surface);
    return true;
}

void snake_render(snake_t *snake, SDL_Renderer *renderer, bool secondSnake) {
    assert(snake);
    iterator_t *it = list_iterator_create(&snake->body, START_FRONT);
    SDL_Point center = {SNAKE_TEXTURE_SIZE_X / 2, SNAKE_TEXTURE_SIZE_Y / 2};
    for (size_t i = 0; i < snake->lenght; i++) {
        snake_node_t *snake_node = iterator_data(it);
        SDL_Rect src;
        if(i == 0)
            src = (SDL_Rect){0, 0, 50, 50};
        else if(i == snake->lenght - 1)
            src = (SDL_Rect){100, 0, 50, 50};
        else
            src = (SDL_Rect){50, 0, 50, 50};
        SDL_Rect dst = {(int) (snake_node->position.x - SNAKE_TEXTURE_SIZE_X / 2),
                        (int) (snake_node->position.y - SNAKE_TEXTURE_SIZE_Y / 2),
                        SNAKE_TEXTURE_SIZE_X, SNAKE_TEXTURE_SIZE_Y};
        SDL_Texture *snake_texture;
        snake_texture = snake_texture1;//on charge la texture du primer snake
        if(secondSnake)//si c'est le deuxième on charge l'autre
            snake_texture = snake_texture2;
        if (SDL_RenderCopyEx(renderer, snake_texture, &src, &dst, snake_node->angle * 180 / M_PI + 90, &center,
                             SDL_FLIP_NONE))
            fprintf(stderr, "SDL_RenderCopyEx(): %s\n", SDL_GetError());
        it = iterator_next(it);
    }
    iterator_destroy(it);
}