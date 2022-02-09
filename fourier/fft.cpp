#include "fft.h"

// Fourier transform using a discrete integration
double FFT::integral (double (*fn) (double), double start, double end, double dt)
{
    double s = 0.f;
    for (double q = start; q <= end; s += fn (q) * dt, q += dt);
    return s;
}

// Discrete fourier transform the usual way
std::vector<Phasor> FFT::dft (std::vector<Complex> &func_samples)
{
    double N = func_samples.size();
    std::vector<Phasor> phasors ((size_t) N);
    // Cn = Sum [k = 1 .. N] {f[k] * exp(-i 2pi n k / N)}
    Complex Cn = 0.;
    for (int n = 0; n < N; n++) {
        for (int k = 0; k < N; k++) {
            double pchunk = ((double) n) * ((double) k) / ((double) N);
            // 1 * exp (-i 2pi n k / N)
            Complex tempZ (Polar {
                1.f,
                -2 * PI * pchunk
            });
            // updating the sum
            Cn = Cn + func_samples[n] * tempZ;
        }
        Cn = Cn / N;
        phasors[n] = {
            Cn.toPolar (),  // angle, amplitude data
            (double) n      // frequency 
        };
    }

    return phasors;
}