    #include "element.h"

SDL_Texture **element_textures;

/* Init */

void element_init(element_t *element, const point_t *position, int type) {
    assert(element);
    element->position = *position;
    element->type = type;
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

/* Effects */

static void element_effect_apple(snake_t *snake) {
    assert(snake);
    snake_grow(snake);
    snake->score += 100;
}

static void element_effect_bombe(snake_t *snake) {
    assert(snake);
    snake_diminish(snake);
    snake->score -= 50;
}

static void element_effect_wall(snake_t *snake) {
    assert(snake);
    while (snake->lenght < 0)
        snake_diminish(snake);
    snake->lenght -= 1000;
}

static void element_effect_laser(snake_t *snake) {
    // TODO
}

void element_effect(element_t *element, snake_t *snake) {
    assert(element && snake);
    switch (element->type) {
        case ELEMENT_APPLE:
            element_effect_apple(snake);
            break;
        case ELEMENT_BOMBE:
            element_effect_bombe(snake);
            break;
        case ELEMENT_WALL:
            element_effect_wall(snake);
            break;
        case ELEMENT_LASER:
            element_effect_laser(snake);
            break;
        default:
            break;
    }
}

/* Render */

static void element_render_apple(element_t *element, SDL_Renderer *renderer) {
    assert(element && renderer);
    SDL_Rect dst = {(int) element->position.x - 16, (int) element->position.y - 16, 32, 32};
    SDL_RenderCopy(renderer, element_textures[ELEMENT_APPLE], NULL, &dst);
}

static void element_render_bombe(element_t *element, SDL_Renderer *renderer) {
    assert(element && renderer);
    SDL_Rect dst = {(int) element->position.x - 16, (int) element->position.y - 16, 32, 32};
    SDL_RenderCopy(renderer, element_textures[ELEMENT_BOMBE], NULL, &dst);
}

static void element_render_wall(element_t *element, SDL_Renderer *renderer) {
    assert(element && renderer);
    SDL_Rect dst = {(int) element->position.x - 16, (int) element->position.y - 16, 32, 32};
    SDL_RenderCopy(renderer, element_textures[ELEMENT_WALL], NULL, &dst);
}

static void element_render_laser(element_t *element, SDL_Renderer *renderer) {
    assert(element && renderer);
    SDL_Rect dst = {(int) element->position.x - 16, (int) element->position.y  - 16, 32, 32};
    SDL_RenderCopy(renderer, element_textures[ELEMENT_LASER], NULL, &dst);
}

void element_render(element_t *element, SDL_Renderer *renderer) {
    assert(element && renderer);
    switch (element->type) {
        case ELEMENT_APPLE:
            element_render_apple(element, renderer);
            break;
        case ELEMENT_BOMBE:
            element_render_bombe(element, renderer);
            break;
        case ELEMENT_WALL:
            element_render_wall(element, renderer);
            break;
        case ELEMENT_LASER:
            element_render_laser(element, renderer);
            break;
        default:
            break;
    }
}

/* Load textures */

bool element_load_texture(SDL_Renderer *renderer) {
    assert(renderer);
    element_textures = calloc(4, sizeof(SDL_Surface *));
    if (!element_textures) {
        perror("calloc():");
        return false;
    }

    /* ELEMENT APPLE */
    SDL_Surface *surface = IMG_Load("../res/element/apple.png");
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP(): %s\n", SDL_GetError());
        return false;
    }
    element_textures[ELEMENT_APPLE] = SDL_CreateTextureFromSurface(renderer, surface);
    if (!element_textures[ELEMENT_APPLE]) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(surface);

    /* ELEMENT BOMBE */
    surface = IMG_Load("../res/element/bombe.png");
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP(): %s\n", SDL_GetError());
        return false;
    }
    element_textures[ELEMENT_BOMBE] = SDL_CreateTextureFromSurface(renderer, surface);
    if (!element_textures[ELEMENT_BOMBE]) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(surface);

    /* ELEMENT WALL */
    surface = IMG_Load("../res/element/wall.png");
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP(): %s\n", SDL_GetError());
        return false;
    }
    element_textures[ELEMENT_WALL] = SDL_CreateTextureFromSurface(renderer, surface);
    if (!element_textures[ELEMENT_WALL]) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(surface);

    /* ELEMENT LASER */
    surface = IMG_Load("../res/element/laser.png");
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_LoadBMP(): %s\n", SDL_GetError());
        return false;
    }
    element_textures[ELEMENT_LASER] = SDL_CreateTextureFromSurface(renderer, surface);
    if (!element_textures[ELEMENT_LASER]) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateTextureFromSurface(): %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(surface);
    return true;
}


