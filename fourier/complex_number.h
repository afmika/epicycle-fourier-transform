#pragma once

#include "constants.h"
#include <iostream>
#include <cmath>

struct Polar {
    double amplitude;
    double angle;
    Polar (double amp, double ang);
    Polar ();
    std::string str () const;
    friend std::ostream& operator<<(std::ostream& os, const Polar& polar);
};


struct Phasor {
    Polar polar_data;
    double freq;
    Phasor (Polar polar, double fr);
    Phasor ();
    std::string str () const;
    friend std::ostream& operator<<(std::ostream& os, const Phasor& phasor);
};

class Complex {
    public:
        double x, y;
        Complex (double x);
        Complex (double x, double y);
        Complex (Polar polar);
        Complex ();

        double amplitude () const;
        double angle () const;
        Polar toPolar () const;

        Complex operator + (Complex other);
        Complex operator - (Complex other);
        Complex operator * (Complex other);
        Complex operator * (double k);
        Complex operator / (Complex other);
        Complex operator / (double k);

        std::string str () const;
        friend std::ostream& operator<<(std::ostream& os, const Complex& obj);
};