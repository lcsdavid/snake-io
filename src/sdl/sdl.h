#ifndef SNAKE_IO_NOM_H
#define SNAKE_IO_NOM_H

#include <stdbool.h>
#include <stdio.h>

#include <SDL_image.h>
#include <SDL_render.h>

bool init();

void close();

SDL_Renderer *get_renderer();

SDL_Texture *load_texture(const char *file);


#endif
