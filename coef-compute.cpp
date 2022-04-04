/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <iostream>
#include <vector>

#include "fourier/complex_number.h"
#include "fourier/fft.h"

void logInfo (std::string infos) {
    // std::cout << "\033\143";
    std::cout << infos;
}

void logError (std::string err) {
    // std::cout << "\033\143";
    std::cerr << err;
}

double sround (double v) {
    double d = 10;
    return std::round (v / d) * d;
}

void help () {
    logInfo ("Raw DFT\n");
    logInfo ("coef-compute [-brute|-math] your_file.txt\n");
}

void displayBrute (std::vector<Phasor> &phasors) {
    for (auto &phasor : phasors) {
        logInfo (phasor.str() + "\n");
    }
}

void displayMath (std::vector<Phasor> &phasors) {
    std::string real = "", img = "";
    bool start = true;
    for (auto &phasor : phasors) {
        char buff1[100], buff2[100];
        double amp = phasor.polar_data.amplitude;
        double angle = phasor.polar_data.angle;
        double freq = phasor.freq;
        // polar_data.amplitude,
        // time * freq + polar_data.angle
        snprintf(
            buff1, sizeof(buff1), 
            "%.2f * cos(2 * pi *%.2f * x + %.2f)", 
            amp, freq, angle
        );

        snprintf(
            buff2, sizeof(buff2), 
            "%.2f * sin(2 * pi * %.2f * x + %.2f)", 
            amp, freq, angle
        );

        if (!start) {
            real += "+";
            img += "+";
        }

        real += std::string(buff1);
        img += std::string(buff2);
        start = false;
    }
    logInfo (real + "\n-----\n");
    logInfo (img);
}

int main (int argc, const char* argv[]) {
    if (argc == 1) {
        help ();
        return 0;
    }

    if (argc == 2) {
        std::string file = argv[1];
        logInfo ("Source : " + file + "\n\n");
        std::vector<Complex> samples = FFT::loadSamplesFromFile (file);
        std::vector<Phasor> phasors = FFT::dft (samples, true);
        displayBrute (phasors);
    }

    std::vector<std::string> choices = {
        "-brute", "-math"
    };

    std::string meth = argv[1];
    std::string file = argv[2];
    bool valid = false;
    for (auto &choice : choices) {
        if (choice.compare(meth) == 0)
            valid = true;
    }

    if (!valid) {
        logError ("Bad command !");
        help ();
        return 0;
    }
    
    std::vector<Complex> samples = FFT::loadSamplesFromFile (file);
    std::vector<Phasor> phasors = FFT::dft (samples, true);

    if (meth.compare(choices[0]) == 0) {
        displayBrute (phasors);
    } else {
        displayMath (phasors); // sum sin and cosine
    }

	return 0;
}