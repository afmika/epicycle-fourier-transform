#pragma once

#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include "complex_number.h"

namespace FFT {
    // Discrete integration
    double integral (double (*fn) (double), double start, double end, double dt = 0.001f);
    
    // Discrete fourier transform the usual way
    std::vector<Phasor> dft (std::vector<Complex> &func_samples, bool do_sort = false);
    std::vector<Complex> loadSamplesFromFile (std::string filename);
};