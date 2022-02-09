#include "../fourier/complex_number.h"
#include <iostream>
#include <vector>

int main () {
    std::cout << "functional tests\n";
    std::vector<Complex> tests {
        {2, -2}, {-1, 1}, {-3, -3}, {0, -0.5}
    };

    for (auto &test : tests) {
        Polar polar = test.toPolar();
        Complex recovered (polar);
        Complex diff = recovered - test;
        std::cout
            << "--" << polar
            << " :: recovered " << recovered
            << " | tested : " << (test)
            << " (diff " << diff << ")" // should get 0
            << '\n';
    }

    Complex q (4, -3), t (-7, 2), s (1, -1), e = -2;
    std::cout << "operator test\n";
    Complex res = q * t - s / t; // ~-21.830189 + 28.905660i
    std::cout << "ans : " << res << '\n';
    std::cout << " -polar : " << res.toPolar () << '\n';
    std::cout << "double : " << e * res << '\n';
    std::cout << " -polar : " << (e * res).toPolar () << '\n';

    return 0;
}