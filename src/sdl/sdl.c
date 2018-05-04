#include "sdl.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer;

bool init() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init(): %s\n", SDL_GetError());
        return false;
    }
    /*if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        fprintf(stderr, "IMG_Init(): %s\n", SDL_GetError());
        return false;
    }
     */
    SDL_CreateWindowAndRenderer(800, 480, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    printf("Level 1\n");
    return true;
}

void close() {
    if(window)
        SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

SDL_Renderer *get_renderer() {
    return renderer;
}

SDL_Texture *load_texture(const char *file) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, file);
    if(!texture)
        fprintf(stderr, "IMG_LoadTexture(): %s\n", SDL_GetError());
    return texture;
}

