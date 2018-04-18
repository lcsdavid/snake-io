#include "button.h"

button_t *button_create(char *desc, int x, int y, int w, int h) {
    button_t *button = calloc(1, sizeof(button_t));
    if(!button) {
        perror("calloc():");
        return NULL;
    }
    *button = (button_t){desc, x, y, w, h, false};
    return button;
}

void button_delete(button_t *button) { free(button); }


void button_select(button_t *button) { button->selected = true; }

void button_deselect(button_t *button) { button->selected = false; }

bool button_is_selected(const button_t *button) { return button->selected; }