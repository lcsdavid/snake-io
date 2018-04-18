#include "menu.h"

SDL_Texture* menu_texture;

menu_t *menu_create(menu_desc_t descriptor, list_t button_list, list_t submenu_list, bool displayed) {
    menu_t *menu = calloc(1, sizeof(menu_t));
    if(!menu) {
        perror("calloc():");
        return NULL;
    }
    *menu = (menu_t){descriptor, button_list, submenu_list, displayed};
    return menu;
}

void menu_delete(menu_t *menu) {
    assert(menu);
    for_each(&menu->button_list, (void (*)(void *)) &button_delete);
    list_clear(&menu->button_list);
    for_each(&menu->submenu_list, (void (*)(void *)) &menu_delete);
    list_clear(&menu->submenu_list);
    free(menu);
}

void menu_init(menu_t *menu) {
    menu->button_list = {NULL, NULL};
    button_t *b = button_create("Scénario", 20, 20, 100, 50);
    list_push_back(&menu->button_list, b);
    b = button_create("Versus",0,0,0,0);
    list_push_back(&menu->button_list, b);
    b = button_create("Options",0,0,0,0);

    menu->submenu_list = {NULL, NULL};


    menu->displayed = true;
}