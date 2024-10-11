#ifndef RECT2_HPP
#define RECT2_HPP

#include <ostream>

#include "Vec2.hpp"

class Rect2
{
public:
    Vec2 origin;
    Vec2 size;

    Rect2(Vec2 origin, Vec2 size);
    Rect2(float x, float y, float w, float h);
    Rect2();

    friend std::ostream &operator<<(std::ostream &stream, const Rect2 &rect);

    Vec2 half_size() const;
    Vec2 center() const;

    float left() const;
    float right() const;
    float top() const;
    float bottom() const;

    bool contains(Vec2 position) const;
};

#endif