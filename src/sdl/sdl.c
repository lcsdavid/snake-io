#include "sdl.h"

SDL_Window *window;
SDL_Renderer *renderer;

bool sdl_init() {
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER)) {
        fprintf(stderr, "SDL_Init(): %s\n", SDL_GetError());
        return false;
    }
    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        fprintf(stderr, "IMG_Init(): %s\n", SDL_GetError());
        return false;
    }
    SDL_CreateWindowAndRenderer(800, 480, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    return true;
}

void sdl_close(SDL_Window *window) {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

SDL_Renderer *get_renderer() {
    return renderer;
}

SDL_Texture *sdl_load_texture(SDL_Renderer *renderer, const char *file) {
    SDL_Texture *texture = IMG_LoadTexture(renderer, file);
    if(!texture)
        fprintf(stderr, "IMG_LoadTexture(): %s\n", SDL_GetError());
    return texture;
}

void sdl_render_texture_resized(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h) {
    SDL_Rect dst = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void sdl_render_texture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    sdl_render_texture_resized(renderer, texture, x, y, w, h);
}