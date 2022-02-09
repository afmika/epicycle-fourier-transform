#include "complex_number.h"

Complex::Complex (double x) : x(x)
{
    this->x = x;
}

Complex::Complex (double x, double y) : x(x), y(y)
{
    this->x = x; this->y = y;
}

Complex::Complex ()
{
    x = 0; y = 0;
}

Complex::Complex (Polar polar)
{
    x = polar.amplitude * std::cos (polar.angle);
    y = polar.amplitude * std::sin (polar.angle);
}

double Complex::amplitude () const
{
    return std::sqrt (x * x + y * y);
}

double Complex::angle () const
{
    return std::atan2 (y, x);
}

Polar Complex::toPolar () const
{
    return {amplitude(), angle()};
}


Complex Complex::operator + (Complex other)
{
    return {x + other.x, y + other.y};
}

Complex Complex::operator - (Complex other)
{
    return {x - other.x, y - other.y};
}

Complex Complex::operator * (Complex other)
{
    return {x * other.x - y * other.y, other.y * x + other.x * y};
}

Complex Complex::operator / (Complex other)
{
    Polar opolar = other.toPolar ();
    Polar curr = toPolar ();
    Polar polarDiv = {
        curr.amplitude / opolar.amplitude,
        curr.angle - opolar.angle
    };
    return Complex (polarDiv);
}

Complex Complex::operator / (double n)
{
    return {x / n, y / n};
}

std::string Complex::str () const
{
    char str[50];

    if (std::fabs(y) < EPS) {
        sprintf (str, "%f", x);
        return str;
    }

    if (std::fabs(x) < EPS) {
        sprintf (str, "%fi", y);
        return str;
    }

    sprintf (str, "%f %c %fi", x, y < 0 ? '-' : '+', std::fabs(y));
    return str;
}

std::ostream& operator<<(std::ostream& os, const Complex& obj)
{
    os << obj.str ();
    return os;
}

// polar form
Polar::Polar (double amp, double ang) : amplitude(amp), angle(ang)
{
    amplitude = amp; angle = ang;
}

Polar::Polar ()
{
}

std::string Polar::str () const
{
    char str[50];
    sprintf (str, "[amp=%f, angle=%f]", amplitude, angle);
    return str;
}

std::ostream& operator<<(std::ostream& os, const Polar& polar)
{
    os << polar.str ();
    return os;
}

// phasor
Phasor::Phasor (Polar polar, double fr) : polar_data (polar), freq (fr)
{
    polar_data = polar; freq = fr;
}

Phasor::Phasor ()
{
}

std::string Phasor::str () const
{
    char str[50];
    sprintf (str, "[amp=%f, angle=%f, freq=%f]", polar_data.amplitude, polar_data.angle, freq);
    return str;
}

std::ostream& operator<<(std::ostream& os, const Phasor& phasor)
{
    os << phasor.str ();
    return os;
}