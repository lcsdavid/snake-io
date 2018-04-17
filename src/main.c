#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include <SDL.h>


bool sdl_init(SDL_Window **, SDL_Renderer **);
void sdl_close(SDL_Window *);

void input();
void render();
void update();

int main(int argc, char *argv[]) {
	SDL_Window *sdl_window = NULL;
	SDL_Renderer *sdl_renderer = NULL;
	if(!sdl_init(&sdl_window, &sdl_renderer))
		return -1;


	return 0;
}






bool sdl_init(SDL_Window **sdl_window, SDL_Renderer **sdl_renderer) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
		return false;
	}
	SDL_CreateWindowAndRenderer(800, 480, 0, sdl_window, sdl_renderer);
	SDL_SetRenderDrawColor(*sdl_renderer, 255, 255, 255, 255);
	SDL_RenderClear(*sdl_renderer);
	SDL_RenderPresent(*sdl_renderer);
	return true;
}

void sdl_close(SDL_Window *sdl_window) {
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void input() {
    SDL_Event event;
    if(!SDL_PollEvent(&event))
        return;
    switch(event.type) {
        default:
            break;
    }
}
