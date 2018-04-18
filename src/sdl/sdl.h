#ifndef SNAKE_IO_NOM_H
#define SNAKE_IO_NOM_H

#include <stdbool.h>
#include <stdio.h>

#include <SDL_image.h>
#include <SDL_render.h>

bool sdl_init();

void sdl_close(SDL_Window *window);

SDL_Renderer *get_renderer();

SDL_Texture *sdl_load_texture(SDL_Renderer *renderer, const char *file);

void sdl_render_texture_resized(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h);

void sdl_render_texture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y);

#endif
