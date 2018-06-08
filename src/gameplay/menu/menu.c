#include "menu.h"

// SDL_Texture* menu_texture;

menu_t *menu_create(menu_desc_t descriptor, bool displayed) {
    menu_t *menu = calloc(1, sizeof(menu_t));
    if(!menu) {
        perror("calloc():");
        return NULL;
    }
    *menu = (menu_t){descriptor, (list_t){NULL, NULL}, (list_t){NULL, NULL}, displayed};
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

menu_t *menu_init() {
    menu_t *main_menu = menu_create(MAIN, true);
    button_t *scenario = button_create("Scénario", 0, 0, 0, 0, true, (void (*)()) &menu_init);
    list_push_back(&main_menu->button_list, scenario);
    return main_menu;
}