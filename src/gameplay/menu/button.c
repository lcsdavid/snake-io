#include "button.h"

bool button_is_selected(const button_t *button) {
    return button->selected;
}