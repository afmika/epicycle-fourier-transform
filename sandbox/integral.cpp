#include "../fourier/fft.h"
#include <iostream>
#include <vector>

double f (double x) {
    return 1 / x;
}

int main () {
    // ~ln(2)
    std::cout << FFT::integral (&f, 1, 2);
    return 0;
}