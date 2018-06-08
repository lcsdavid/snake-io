#include "element.h"

SDL_Texture *element_texture_apple;
SDL_Texture *element_texture_bombe;
SDL_Texture *element_texture_wall;
SDL_Texture *element_texture_laser;

void init_apple(element_t *element, const point_t *position) {
    element->position = *position;
    element->type = ELEMENT_APPLE;
    element->element_effect = &element_effect_apple;
    element->element_render = &element_render_apple;
}

void init_bombe(element_t *element, const point_t *position) {
    element->position = *position;
    element->type = ELEMENT_BOMBE;
    element->element_effect = &element_effect_bombe;
    element->element_render = &element_render_bombe;
}

void init_wall(element_t *element, const point_t *position) {
    element->position = *position;
    element->type = ELEMENT_WALL;
    element->element_effect = &element_effect_wall;
    element->element_render = &element_render_wall;
}

void init_laser(element_t *element, const point_t *position){
    element->position = *position;
    element->type = ELEMENT_LASER;
    element->element_render = &element_render_laser;

}

void element_init(element_t *element, const point_t *position, int type) {
    assert(element);
    if (type == ELEMENT_APPLE)
        init_apple(element, position);
    else if (type == ELEMENT_BOMBE)
        init_bombe(element, position);
    else if (type == ELEMENT_WALL)
        init_wall(element, position);
    else if (type == ELEMENT_LASER)
        init_laser(element, position);
}

element_t *element_create(const point_t *position, int type) {
    element_t *element = calloc(1, sizeof(element_t));
    if (!element) {
        perror("calloc():");
        return NULL;
    }
    element_init(element, position, type);
    return element;
}

void element_render_apple(element_t *element, SDL_Renderer *renderer) {
    SDL_Log("%lf %lf", element->position.x, element->position.y);
    SDL_Rect dst = {element->position.x, element->position.y, 32, 32};
    SDL_RenderCopy(renderer, element_texture_apple, NULL, &dst);
}

void element_render_bombe(element_t *element, SDL_Renderer *renderer) {
    SDL_Log("%lf %lf", element->position.x, element->position.y);
    SDL_Rect dst = {element->position.x, element->position.y, 32, 32};
    SDL_RenderCopy(renderer, element_texture_bombe, NULL, &dst);
}

void element_render_wall(element_t *element, SDL_Renderer *renderer) {
    SDL_Log("%lf %lf", element->position.x, element->position.y);
    SDL_Rect dst = {element->position.x, element->position.y, 32, 32};
    SDL_RenderCopy(renderer, element_texture_wall, NULL, &dst);
}

void element_render_laser(element_t *element, SDL_Renderer *renderer){

    SDL_Log("%lf %lf", element->position.x, element->position.y);
    SDL_Rect dst = {element->position.x, element->position.y, 32, 32};
    SDL_RenderCopy(renderer, element_texture_laser, NULL, &dst);
}

void element_effect_apple(snake_t *snake) {
    assert(snake);
    snake_grow(snake);
}

void element_effect_bombe(snake_t *snake) {
    assert(snake);
    snake_diminish(snake);
}

void element_effect_wall(snake_t *snake) {
    assert(snake);
    while (snake->lenght < 0) {
        snake_diminish(snake);
    }
}

bool element_load_texture(SDL_Renderer *renderer) {
    assert(renderer);
    SDL_Surface *element_surface = IMG_Load("../res/element/apple.png");
    if (!element_surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP(): %s\n", SDL_GetError());
        return false;
    }
    element_texture_apple = SDL_CreateTextureFromSurface(renderer, element_surface);
    if (!element_texture_apple) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(element_surface);

    // Chargement des bombes
    element_surface = IMG_Load("../res/element/bombe.png");
    if (!element_surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP(): %s\n", SDL_GetError());
        return false;
    }
    element_texture_bombe = SDL_CreateTextureFromSurface(renderer, element_surface);
    if (!element_texture_bombe) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(element_surface);

    // Chargement des murs
    element_surface = IMG_Load("../res/element/wall.png");
    if (!element_surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP(): %s\n", SDL_GetError());
        return false;
    }
    element_texture_wall = SDL_CreateTextureFromSurface(renderer, element_surface);
    if (!element_texture_wall) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        return false;
    }

    // Chargement des laser
    element_surface = IMG_Load("../res/element/laser.png");
    if (!element_surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP(): %s\n", SDL_GetError());
        return false;
    }
    element_texture_laser = SDL_CreateTextureFromSurface(renderer, element_surface);
    if (!element_texture_laser) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(element_surface);
    return true;
}


