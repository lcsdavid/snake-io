#include "input.h"

void input() {
    SDL_Event event;
    if(!SDL_PollEvent(&event))
        return;
    switch(event.type) {
        case SDL_KEYUP || SDL_KEYDOWN:
            keyboard_input(event);
            break;
        default:
            break;
    }
}

void keyboard_input(SDL_Event event) {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_LEFT:
            snake_change_direction(get_player1(), 1);
            break;
        case SDL_SCANCODE_RIGHT:
            snake_change_direction(get_player1(), 0);
            break;
        default:
            break;
    }
}