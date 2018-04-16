#ifndef SNAKE_IO_MENU_H
#define SNAKE_IO_MENU_H

#include <stdbool.h>
#include <stdint.h>
#include "../../standard/list/list.h"

typedef struct menu {
    list_t button_list;
    list_t submenu_list;

    // sdl surface -> image
} menu_t ;

void menu_init(menu_t *menu /*, surface etc*/);


#endif