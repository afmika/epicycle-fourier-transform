#include "../fourier/fft.h"
#include "../fourier/complex_number.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<Complex> testSample () {
    std::vector<Complex> list;
    for (double k = -8.; k < 8.; k += 0.5) {
        list.push_back (k * k * k + 2 * k);
    }
    return list;
}

int main () {
    std::vector<Complex> list = testSample ();
    std::vector<Phasor> result = FFT::dft (list, true);

    for (auto &phasor : result) {
        Polar p = phasor.polar_data;
        std::cout << Complex(p) << " :: " << phasor << ", " << (p.angle * 180 / PI) << "deg" << '\n';
    }
    return 0;
}