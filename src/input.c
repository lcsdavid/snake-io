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

            break;
        case SDL_SCANCODE_RIGHT:

            break;
        default:
            break;
    }
}