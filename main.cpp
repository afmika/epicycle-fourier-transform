/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "SDL.h"
#include <iostream>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


SDL_Rect rect = {5, 5, 100, 100};
int dx = 1, dy = 1;

void doStuff (SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
    SDL_RenderFillRect (renderer, &rect);
    if (rect.x <= 0 || rect.x + rect.w > SCREEN_WIDTH) dx *= -1;
    if (rect.y <= 0 || rect.y + rect.h > SCREEN_HEIGHT) dy *= -1;
    rect.x += dx;
    rect.y += dy;
}

int main (int argc, char** argv) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // init SDL Video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return 0;
    }

    window = SDL_CreateWindow ("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf ("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    bool animate = true;
    while (animate) {
        SDL_Event event;
        SDL_PollEvent (&event);
        switch (event.type) {
            case SDL_QUIT:
                animate = false;
                break;
        }
        SDL_SetRenderDrawColor (renderer, 0xFF, 0xFF, 0xFF, 0xFF); // color for drawing
        SDL_RenderClear (renderer); // clear the entire screen with our selected color

        ////////////////////
        doStuff (renderer);
        ///////////////////
        
        // renders the prepared 'drawing buffer'
        SDL_RenderPresent (renderer);
        SDL_Delay (1000 / 60);
    }

    SDL_DestroyWindow (window);
    SDL_Quit();
	return 0;
}