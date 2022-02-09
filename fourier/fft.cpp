#include "fft.h"

// Fourier transform using a discrete integration
double FFT::integral (double (*fn) (double), double start, double end, double dt)
{
    double s = 0.f;
    for (double q = start; q <= end; s += fn (q) * dt, q += dt);
    return s;
}

// Discrete fourier transform the usual way
std::vector<double> FFT::dft (std::vector<double> &func_samples)
{
}