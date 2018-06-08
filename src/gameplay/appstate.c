#include "appstate.h"
#include "gamestate.h"

SDL_Texture *texture_water;

static bool load_texture(appstate_t *appstate) {
    SDL_Surface *surface = IMG_Load("../res/floor_is_water.png");
    texture_water = SDL_CreateTextureFromSurface(appstate->renderer, surface);
    if (!snake_load_texture(appstate->renderer))
        return false;
    if (!element_load_texture(appstate->renderer))
        return false;
    return true;
}


bool appstate_init(appstate_t *appstate) {
    srand((unsigned int) time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init(): %s\n", SDL_GetError());
        return false;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init(): %s\n", SDL_GetError());
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
        return -1;
    Mix_Music *music = Mix_LoadMUS("../res/music.mp3");
    if (music == NULL)
        return false;
    if (Mix_PlayMusic(music, -1) == -1)
        return -1;

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

    if (!load_texture(appstate))
        return false;

    gamestate_init(&appstate->gamestate);
    return true;
}

void input(appstate_t *appstate) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_WINDOWEVENT_CLOSE || event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
            appstate->end = true;
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    /* Player One */
    if (state[SDL_GetScancodeFromKey(SDLK_LEFT)])
        snake_change_direction(&appstate->gamestate.player_one, true);
    if (state[SDL_GetScancodeFromKey(SDLK_RIGHT)])
        snake_change_direction(&appstate->gamestate.player_one, false);
    if (state[SDL_GetScancodeFromKey(SDLK_8)]) /* Test grow() */
        snake_grow(&appstate->gamestate.player_one);
    if (state[SDL_GetScancodeFromKey(SDLK_9)]) /* Test diminish() */
        snake_diminish(&appstate->gamestate.player_one);
    /* Player Two */
    if (state[SDL_GetScancodeFromKey(SDLK_q)])
        if (appstate->gamestate.multiplayer)
            snake_change_direction(&appstate->gamestate.player_two, true);
    if (state[SDL_GetScancodeFromKey(SDLK_d)])
        if (appstate->gamestate.multiplayer)
            snake_change_direction(&appstate->gamestate.player_two, false);
    /* New player */
    if (state[SDL_GetScancodeFromKey(SDLK_n)]) {
        if (!appstate->gamestate.multiplayer) {
            appstate->gamestate.multiplayer = true;
            point_t start = new_point(&appstate->gamestate);
            point_t point = new_point(&appstate->gamestate);
            list_push_front(&appstate->gamestate.elements, element_create(&point, ELEMENT_APPLE));
            snake_init(&appstate->gamestate.player_two, &start, 0);
        }
    }
    if (state[SDL_GetScancodeFromKey(SDLK_a)]) {
        if (appstate->gamestate.modeArcade) {
            appstate->gamestate.modeArcade = false;
        } else {
            appstate->gamestate.modeArcade = true;
        }
    }
    /* Fullscreen */
    if (state[SDL_GetScancodeFromKey(SDLK_TAB)])
        SDL_SetWindowFullscreen(appstate->window,
                                SDL_GetWindowFlags(appstate->window) & SDL_WINDOW_FULLSCREEN_DESKTOP ? 0
                                                                                                     : SDL_WINDOW_FULLSCREEN_DESKTOP);

}

void render(appstate_t *appstate) {
    SDL_RenderClear(appstate->renderer);
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



