#include "appstate.h"

SDL_Texture *texture_water;

static bool load_texture(appstate_t *appstate) {
    SDL_Surface *surface = IMG_Load("../res/floor_is_water.png");
    texture_water = SDL_CreateTextureFromSurface(appstate->renderer, surface);
    if (!snake_load_texture(appstate->renderer))
        return false;
    if(!element_load_texture(appstate->renderer))
        return false;
    return true;
}




bool appstate_init(appstate_t *appstate) {
    srand((unsigned int) time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init(): %s\n", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init(): %s\n", SDL_GetError());
        return false;
    }
    SDL_Window *window = SDL_CreateWindow("Test SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow(): %s\n", SDL_GetError());
        return false;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer(): %s\n", SDL_GetError());
        return false;
    }
    appstate->window = window;
    appstate->renderer = renderer;
    appstate->end = false;

    if(!load_texture(appstate))
        return false;

    gamestate_init(&appstate->gamestate);


    return true;
}

void input(appstate_t *appstate) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_WINDOWEVENT_CLOSE || event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
            appstate->end = true;
        if (event.type == SDL_KEYDOWN) {
            /* Player One */
            if (event.key.keysym.sym == SDLK_LEFT)
                snake_change_direction(&appstate->gamestate.player_one, true);
            if (event.key.keysym.sym == SDLK_RIGHT)
                snake_change_direction(&appstate->gamestate.player_one, false);
            if (event.key.keysym.sym == SDLK_8) /* Test grow() */
                snake_grow(&appstate->gamestate.player_one);
            if (event.key.keysym.sym == SDLK_9) /* Test diminish() */
                snake_diminish(&appstate->gamestate.player_one);
            /* Player Two */
            if (event.key.keysym.sym == SDLK_q)
                if (appstate->gamestate.multiplayer)
                    snake_change_direction(&appstate->gamestate.player_two, true);
            if (event.key.keysym.sym == SDLK_d)
                if (appstate->gamestate.multiplayer)
                    snake_change_direction(&appstate->gamestate.player_two, false);
            /* New player */
            if (event.key.keysym.sym == SDLK_KP_ENTER) {
                appstate->gamestate.multiplayer = true;
                point_t start = new_point(&appstate->gamestate);
                snake_init(&appstate->gamestate.player_two, &start, 0);
            }
            /* Fullscreen */
            if (event.key.keysym.sym == SDLK_TAB)
                SDL_SetWindowFullscreen(appstate->window,
                                        SDL_GetWindowFlags(appstate->window) & SDL_WINDOW_FULLSCREEN_DESKTOP ? 0
                                                                                                             : SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
    }
}

void render(appstate_t *appstate) {
    SDL_RenderClear(appstate->renderer);
    //SDL_SetRenderDrawColor(appstate->renderer, 15, 78, 234, 255);

    SDL_Rect dst;
    for (int i = 0; i < 75; i++) {
        for (int j = 0; j < 50; j++) {
            dst = (SDL_Rect) {i * 16, j * 16, 16, 16};
            SDL_RenderCopy(appstate->renderer, texture_water, NULL, &dst);
        }
    }

    /* If game running */
    gamestate_render(&appstate->gamestate, appstate->renderer);

    SDL_RenderPresent(appstate->renderer);
    //TODO ajouter un deuxieme joueur et les différents éléments
}

void update(appstate_t *appstate) {
    if (!snake_move(&appstate->gamestate.player_one)) {
        appstate->end = true; //on sort de l'application
        return;
    }//si le serpent se mange lui même
    if (appstate->gamestate.multiplayer)
        if (!snake_move(&appstate->gamestate.player_two))
            appstate->end = true;
    appstate->end = collision(&appstate->gamestate);
}



