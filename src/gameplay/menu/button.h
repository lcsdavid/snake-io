#ifndef SNAKE_IO_BUTTON_H
#define SNAKE_IO_BUTTON_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "../../standard/math/point.h"

/**
 * @struct button_t
 * @brief Object with a size, a position and an effect.
 *
 *
 */
typedef struct button {
    char *desc;
    int x, y;
    int w, h;
    bool selected;

    //void (*effect)();
} button_t ;

button_t *button_create(char *desc, int x, int y, int w, int h);

void button_delete(button_t *button);


void button_select(button_t *button);

void button_deselect(button_t *button);

bool button_is_selected(const button_t *button);

#endif
