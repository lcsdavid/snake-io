#include "element.h"

#include "../appstate.h"
#include "../gamestate.h"

#include "../../standard/math/point.h"

SDL_Texture *element_texture_apple;
SDL_Texture *element_texture_bombe;
SDL_Texture *element_texture_wall;

/* Initialize */

static void init_apple(element_t *element, const point_t *position) {
    assert(element);
    element->position = *position;
    element->type = ELEMENT_APPLE;
}

static void init_bombe(element_t *element, const point_t *position) {
    assert(element);
    element->position = *position;
    element->type = ELEMENT_BOMBE;
}

static void init_wall(element_t *element, const point_t *position) {
    assert(element);
    element->position = *position;
    element->type = ELEMENT_WALL;
}

void element_init(element_t *element, const point_t *position, int type) {
    assert(element);
    if (type == ELEMENT_APPLE)
        init_apple(element, position);
    else if (type == ELEMENT_BOMBE)
        init_bombe(element, position);
    else if (type == ELEMENT_WALL)
        init_wall(element, position);
}

/* Create */

element_t *element_create(const point_t *position, int type) {
    element_t *element = calloc(1, sizeof(element_t));
    if (!element) {
        perror("calloc():");
        return NULL;
    }
    element_init(element, position, type);
    return element;
}

/* Render */

static void element_render_apple(element_t *element, appstate_t* appstate) {
    int padding_x, padding_y;
    SDL_GetWindowSize(appstate->window, &padding_x, &padding_y);
    padding_x = (padding_x - appstate->gamestate->map.size_x) / 2;
    padding_y = (padding_y - appstate->gamestate->map.size_y) / 2;
    SDL_Rect dst = {(int) (padding_x + element->position.x),
                    (int) (padding_y + element->position.y), 32, 32};
    SDL_RenderCopy(appstate->renderer, element_texture_apple, NULL, &dst);
}

static void element_render_bombe(element_t *element, appstate_t* appstate) {
    int padding_x, padding_y;
    SDL_GetWindowSize(appstate->window, &padding_x, &padding_y);
    padding_x = (padding_x - appstate->gamestate->map.size_x) / 2;
    padding_y = (padding_y - appstate->gamestate->map.size_y) / 2;
    SDL_Rect dst = {(int) (padding_x + element->position.x),
                    (int) (padding_y + element->position.y), 32, 32};
    SDL_RenderCopy(appstate->renderer, element_texture_bombe, NULL, &dst);
}

static void element_render_wall(element_t *element, appstate_t* appstate) {
    int padding_x, padding_y;
    SDL_GetWindowSize(appstate->window, &padding_x, &padding_y);
    padding_x = (padding_x - appstate->gamestate->map.size_x) / 2;
    padding_y = (padding_y - appstate->gamestate->map.size_y) / 2;
    SDL_Rect dst = {(int) (padding_x + element->position.x),
                    (int) (padding_y + element->position.y), 32, 32};
    SDL_RenderCopy(appstate->renderer, element_texture_wall, NULL, &dst);
}

void element_render(element_t* element, appstate_t* appstate) {
    assert(element);
    switch (element->type) {
        case ELEMENT_APPLE:
            element_render_apple(element, appstate);
            break;
        case ELEMENT_BOMBE:
            element_render_bombe(element, appstate);
            break;
        case ELEMENT_WALL:
            element_render_wall(element, appstate);
            break;
        default:
            break;
    }
}

/* Action */

static void element_effect_apple(snake_t *snake) {
    assert(snake);
    snake_grow(snake);
}

static bool element_effect_bombe(snake_t *snake) {
    assert(snake);
    if(snake->lenght == 1)
        return false;
    snake_diminish(snake);
    return true;
}

static bool element_effect_wall(snake_t *snake) {
    assert(snake);
    return false;
}

bool element_effect(element_t* element, snake_t* snake) {
    assert(element);
    switch (element->type) {
        case ELEMENT_APPLE:
            element_effect_apple(snake);
            break;
        case ELEMENT_BOMBE:
            return element_effect_bombe(snake);
        case ELEMENT_WALL:
            return element_effect_wall(snake);
        default:
            break;
    }
    return true;
}

/* Load texture */

void element_load_texture(SDL_Renderer *renderer) {
    assert(renderer);
    SDL_Surface *element_surface = IMG_Load("../res/element/apple.png");
    if (!element_surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP(): %s\n", SDL_GetError());
        assert(element_surface);
    }
    element_texture_apple = SDL_CreateTextureFromSurface(renderer, element_surface);
    if (!element_texture_apple) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        assert(element_surface);
    }
    SDL_FreeSurface(element_surface);

    //chargement des bombes
    element_surface = IMG_Load("../res/element/bombe.png");
    if (!element_surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP(): %s\n", SDL_GetError());
        assert(element_surface);
    }
    element_texture_bombe = SDL_CreateTextureFromSurface(renderer, element_surface);
    if (!element_texture_bombe) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        assert(element_surface);
    }
    SDL_FreeSurface(element_surface);

    //chargement des murs
    element_surface = IMG_Load("../res/element/wall.png");
    if (!element_surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP(): %s\n", SDL_GetError());
        assert(element_surface);
    }
    element_texture_wall = SDL_CreateTextureFromSurface(renderer, element_surface);
    if (!element_texture_wall) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        assert(element_surface);
    }
    SDL_FreeSurface(element_surface);
}


