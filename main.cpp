/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "SDL.h"
#include <iostream>
#include <vector>

#include "fourier/complex_number.h"
#include "fourier/fft.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


void drawAll (SDL_Renderer* renderer, std::vector<Phasor> &phasors) {
    SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);

}

int main (int argc, char** argv) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    std::string file = "./datas/pansy-datas.txt";
    std::vector<Complex> samples = FFT::loadSamplesFromFile (file);
    std::vector<Phasor> phasors = FFT::dft (samples, false);

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
        drawAll (renderer, phasors);
        ///////////////////
        
        // renders the prepared 'drawing buffer'
        SDL_RenderPresent (renderer);
        SDL_Delay (1000 / 60);
    }

    SDL_DestroyWindow (window);
    SDL_Quit();
	return 0;
}