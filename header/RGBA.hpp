#ifndef RGBA_HPP
#define RGBA_HPP

#include <ostream>

#include <SFML/Graphics/Color.hpp>

struct RGBA
{
    int r;
    int g;
    int b;
    int a;

    RGBA(int r, int g, int b, int a = 255);
    RGBA();

    static RGBA random(int a = 255);

    static RGBA red(int a = 255) { return RGBA(255, 0, 0, a); }
    static RGBA green(int a = 255) { return RGBA(0, 255, 0, a); }
    static RGBA blue(int a = 255) { return RGBA(0, 0, 255, a); }
    static RGBA white(int a = 255) { return RGBA(255, 255, 255, a); }
    static RGBA black(int a = 255) { return RGBA(0, 0, 0, a); }

    operator sf::Color();

    friend std::ostream &
    operator<<(std::ostream &stream, const RGBA &rgba);
};

#endif