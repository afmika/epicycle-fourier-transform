#pragma once

#include <cmath>
#include <vector>

namespace FFT {
    // Fourier transform using a discrete integration
    double integral (double (*fn) (double), double start, double end, double dt = 0.001f);
    
    // Discrete fourier transform the usual way
    std::vector<double> dft (std::vector<double> &func_samples);
};