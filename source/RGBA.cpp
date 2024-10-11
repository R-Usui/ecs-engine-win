#include "RGBA.hpp"

RGBA::RGBA(int r, int g, int b, int a)
    : r{r}, g{g}, b{b}, a{a}
{
}

RGBA::RGBA()
    : RGBA(255, 255, 255)
{
}

RGBA RGBA::random(int a)
{
    return RGBA(rand() % 256, rand() % 256, rand() % 256, a);
}

RGBA::operator sf::Color()
{
    return sf::Color(r, g, b, a);
}

std::ostream &operator<<(std::ostream &stream, const RGBA &rgba)
{
    stream << "(R=" << rgba.r
           << ", G=" << rgba.g
           << ", B=" << rgba.b
           << ", A=" << rgba.a << ")";
    return stream;
}
