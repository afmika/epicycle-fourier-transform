#pragma once

#include <cmath>
#include <vector>
#include "complex_number.h"

namespace FFT {
    // Fourier transform using a discrete integration
    double integral (double (*fn) (double), double start, double end, double dt = 0.001f);
    
    // Discrete fourier transform the usual way
    std::vector<Phasor> dft (std::vector<Complex> &func_samples);
};