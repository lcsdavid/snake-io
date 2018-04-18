#ifndef SNAKE_IO_MENU_H
#define SNAKE_IO_MENU_H

#include <stdbool.h>
#include <stdint.h>
#include <SDL_surface.h>
#include <SDL_image.h>

#include "button.h"
#include "../../standard/list/list.h"

typedef enum menu_desc {
    MAIN, SCENARIO, VERSUS, ARCADE, SETTINGS
} menu_desc_t ;

typedef struct menu {
    menu_desc_t descriptor;
    list_t button_list;
    list_t submenu_list;
    bool displayed;
} menu_t ;

menu_t *menu_create(menu_desc_t descriptor, list_t button_list, list_t submenu_list, bool displayed);

void menu_delete(menu_t *menu);

void menu_init(menu_t *menu);


#endif
