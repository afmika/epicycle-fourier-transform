/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include "SDL.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

#include "fourier/complex_number.h"
#include "fourier/fft.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const double TX = 250;
const double TY = 250;
std::vector<Complex> points;

void logInfo (std::string infos) {
    std::cout << "\033\143";
    std::cout << infos;
}

Complex computeTipAtTime ( std::vector<Phasor> &phasors, double &t)
{
    Complex tip;
    for (auto &phasor : phasors) {
        // it illustrates the fact that for t = 1s, we got f perfect rounds
        // Phasor currentAngle/amplitude + exp (i * f * t)
        Complex dz (phasor.stateAt (t));
        tip = tip + dz; // overall sum
    }
    points.push_back (tip);
    return tip;
}

void drawAll (SDL_Renderer *renderer, std::vector<Phasor> &phasors, double &t) {
    Complex tip = computeTipAtTime (phasors, t);
    SDL_SetRenderDrawColor (renderer, 255, 0, 0, 255);
    // draw the points
    for (int i = 1, s = points.size(); i < s; i++) {
        Complex oldp = points[i - 1], newp = points[i];
        SDL_RenderDrawLine (renderer, TX + oldp.x, TY + oldp.y, TX + newp.x, TY + newp.y);
    }
    // Log
    // char buffer[50];
    // sprintf (buffer, "Time %.3f s | tip %s | n. points %d", time, tip.str().c_str(), points.size ());
    // logInfo (buffer);
}

int main (int argc, char** argv) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

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
    auto t_start = std::chrono::high_resolution_clock::now();
    double time = 0.;
    double max_freq = phasors[phasors.size () - 1].freq;

    while (animate) {
        SDL_Event event;
        SDL_PollEvent (&event);
        switch (event.type) {
            case SDL_QUIT:
                animate = false;
                break;
        }

        auto t_end = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
        t_start = t_end;

        SDL_SetRenderDrawColor (renderer, 0xFF, 0xFF, 0xFF, 0xFF); // color for drawing
        SDL_RenderClear (renderer); // clear the entire screen with our selected color

        ////////////////////
        if (time < 2 * PI) // 2pi is the total period ie. a perfect round
            drawAll (renderer, phasors, time);
        ////////////////////
        time += 2 * PI / (max_freq + 1.);
        // renders the prepared 'drawing buffer'
        SDL_RenderPresent (renderer);

        SDL_Delay (1000 / 60);
    }

    SDL_DestroyWindow (window);
    SDL_Quit();
	return 0;
}