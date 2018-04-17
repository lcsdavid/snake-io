#ifndef SNAKE_IO_MENU_H
#define SNAKE_IO_MENU_H

#include <stdbool.h>
#include <stdint.h>
#include <SDL_surface.h>
#include <SDL_image.h>
#include "../../standard/list/list.h"

typedef struct menu {
    list_t button_list;
    list_t submenu_list;
    SDL_Surface *sdl_surface;
} menu_t ;

void menu_init(menu_t *menu);


#endif
