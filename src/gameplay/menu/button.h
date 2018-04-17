#ifndef SNAKE_IO_BUTTON_H
#define SNAKE_IO_BUTTON_H

#include <stdbool.h>
#include <stdint.h>

#include <SDL_surface.h>

#include "../../standard/math/point.h"

/**
 * @struct button_t
 * @brief Object with a size, a position and an effect.
 *
 *
 */
typedef struct button {
    void (*effect)();
    uint16_t height;
    uint16_t lenght;
    point_t position;
    bool selected;

    SDL_Surface *sld_surface;
} button_t ;

bool button_is_selected(const button_t *button);

#endif
