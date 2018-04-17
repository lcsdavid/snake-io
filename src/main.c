#include <stdio.h>
#include <stdint.h>
#include "standard/node/node.h"
#include <SDL.h>

/*
int8_t sdl_init(SDL_Window *, SDL_Renderer *);
void sdl_close(SDL_Window *);
*/


void input();
void render();
void update();

int main(int argc, char *argv[]) {
	/*
	SDL_Window *sdl_window = NULL;
	SDL_Renderer *sdl_renderer = NULL;
	if(sdl_init(&sdl_window, &sdl_renderer) == -1)
		return -1;
	 */


	return 0;
}

























/*
int8_t sdl_init(SDL_Window *sdl_window, SDL_Renderer *sdl_renderer) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
		return -1;
	}
	SDL_CreateWindowAndRenderer(800, 480, 0, &window, &renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	return 0;
}

void sdl_close(SDL_Window *sdl_window) {
    SDL_DestroyWindow();
    SDL_Quit();
}

void input() {
    SDL_Event event;
    if(!SDL_PollEvent(&event))
        return;
    switch(event.type) {

    }
}

*/