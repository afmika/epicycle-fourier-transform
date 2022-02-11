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
const double TX = 250;
const double TY = 250;
std::vector<Complex> points;

void logInfo (std::string infos) {
    // std::cout << "\033\143";
    std::cout << infos;
}

void drawCircle (SDL_Renderer *renderer, Complex pos, double radius) {
    if (((int) radius) <= 0) return;
    double n = 20;
    double t = 2. * PI / n;
    Complex old = pos + radius;
    for (int k = 1; k <= n; k++) {
        // (cos t + i sin t) == rotation t rad
        Complex next = pos + Complex(Polar (radius, k * t)); // rotate the current point
        SDL_RenderDrawLine (renderer, TX + old.x, TY + old.y, TX + next.x, TY + next.y);
        old = next;
    }
}

void drawLine (SDL_Renderer *renderer, Complex a, Complex b) {
    SDL_RenderDrawLine (renderer, TX + a.x, TY + a.y, TX + b.x, TY + b.y);
}

void drawArrow (SDL_Renderer *renderer, Complex a, Complex b) {
    double len = 5.;
    drawLine (renderer, a, b);
    Complex d = b - a;
    Complex d1 = Polar(len, d.angle() - PI / 5.);
    Complex d2 = Polar(len, d.angle() + PI / 5.);
    drawLine (renderer, b - d1, b);
    drawLine (renderer, b - d2, b);
}

void drawAll (SDL_Renderer *renderer, std::vector<Phasor> &phasors, double &t) {
    Complex tip;

    SDL_SetRenderDrawColor (renderer, 0, 0, 0xFF, 0x28);
    for (auto phasor : phasors) {
        // it illustrates the fact that for t = 1s, we got f perfect rounds
        // Phasor currentAngle/amplitude + exp (i * f * t)
        Complex dz (phasor.stateAt (t));
        Complex next = tip + dz;
        drawArrow (renderer, tip, next);
        // drawCircle (renderer, tip, dz.amplitude()); // the center will be the previous tip

        tip = next; // update tip
    }
    points.push_back (tip);

    // draw the computed points
    SDL_SetRenderDrawColor (renderer, 0xFF, 0, 0, 0xFF);
    for (int i = 1, s = points.size(); i < s; i++)
        drawLine (renderer, points[i - 1], points[i]);
    
    // Log
    char buffer[50];
    sprintf (buffer, "Time %.3f s | tip %s | n. points %d\n", t, tip.str().c_str(), points.size ());
    logInfo (buffer);
}

int main (int argc, char** argv) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    std::string file = "./datas/pansy-datas.txt";
    std::vector<Complex> samples = FFT::loadSamplesFromFile (file);
    std::vector<Phasor> phasors = FFT::dft (samples, true);

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
    double time = 0.;
    double max_freq = phasors[0].freq + 1.;

    while (animate) {
        SDL_Event event;
        SDL_PollEvent (&event);
        switch (event.type) {
            case SDL_QUIT:
                animate = false;
                break;
        }

        if (time < 2 * PI) { // period
            SDL_SetRenderDrawBlendMode (renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor (renderer, 0xFF, 0xFF, 0xFF, 0xFF); // color for drawing
            SDL_RenderClear (renderer); // clear the entire screen with our selected color
            drawAll (renderer, phasors, time);
            time += 2 * PI / max_freq;
            SDL_RenderPresent (renderer);
        }

        SDL_Delay (1000 / 10);
    }

    SDL_DestroyWindow (window);
    SDL_Quit ();
	return 0;
}