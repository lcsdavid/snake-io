#include "sdl.h"

SDL_Window *window;
SDL_Renderer *renderer;

bool init() {
    SDL_Surface*  field_surface = NULL;
    SDL_Surface*  fruit_surface = NULL;
    SDL_Surface*  shead_surface = NULL;
    SDL_Surface*  snake_surface = NULL;
    SDL_Texture*  field_texture = NULL;
    SDL_Texture*  fruit_texture = NULL;
    SDL_Texture*  shead_texture = NULL;
    SDL_Texture*  snake_texture = NULL;
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
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
    fruit_surface = SDL_LoadBMP("apple.bmp");
    shead_surface = SDL_LoadBMP("head.bmp");
    snake_surface = SDL_LoadBMP("snake.bmp");
    field_surface = SDL_LoadBMP("field.bmp");
    fruit_texture = SDL_CreateTextureFromSurface(renderer, fruit_surface);
    shead_texture = SDL_CreateTextureFromSurface(renderer, shead_surface);
    snake_texture = SDL_CreateTextureFromSurface(renderer, snake_surface);
    field_texture = SDL_CreateTextureFromSurface(renderer, field_surface);
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

