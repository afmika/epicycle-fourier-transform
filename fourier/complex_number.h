#pragma once

#include "constants.h"
#include <iostream>
#include <cmath>

struct Polar {
    double amplitude;
    double angle;
    Polar (double amp, double ang) : amplitude(amp), angle(ang)
    {
        amplitude = amp; angle = ang;
    }

    std::string str () const;
    friend std::ostream& operator<<(std::ostream& os, const Polar& polar);
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

        std::string str () const;
        friend std::ostream& operator<<(std::ostream& os, const Complex& obj);
};