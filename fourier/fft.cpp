#include "fft.h"

// Discrete integration
double FFT::integral (double (*fn) (double), double start, double end, double dt)
{
    double s = 0.f;
    for (double q = start; q <= end; s += fn (q) * dt, q += dt);
    return s;
}

// Discrete fourier transform the usual way
std::vector<Phasor> FFT::dft (std::vector<Complex> &func_samples, bool do_sort)
{
    double N = func_samples.size();
    std::vector<Phasor> phasors ((size_t) N);
    // Cn = Sum [k = 1 .. N] {f[k] * exp(-i 2pi n k / N)}
    Complex Cn;
    for (int n = 1; n <= (int) N; n++) {
        Cn = 0; // reset previous
        for (int k = 0; k < N; k++) {
            double pchunk = ((double) n) * ((double) k) / ((double) N);
            // 1 * exp (-i 2pi n k / N)
            Complex tempZ (Polar {
                1.f,
                -2 * PI * pchunk
            });
            // updating the sum
            Cn = Cn + func_samples[k] * tempZ;
        }
        Cn = Cn / N;
        phasors[n - 1] = {
            Cn.toPolar (),  // angle, amplitude data
            (double) n      // frequency 
        };
    }
    
    if (do_sort) {
        std::sort (phasors.begin(), phasors.end(), [&] (auto a, auto b) {
            return a.polar_data.amplitude < b.polar_data.amplitude;
        });
    }

    return phasors;
}


std::vector<Complex> FFT::loadSamplesFromFile (std::string filename)
{
    std::fstream file (filename, std::ios::in);
    int n = 0;
    file >> n;
    std::vector<Complex> samples (n);
    for (int i = 0; i < n; i++) {
        double x, y;
        file >> x >> y;
        samples[i] = {x, y};
    }
    file.close ();
    return samples;
}