#include "Rect2.hpp"

Rect2::Rect2(Vec2 origin, Vec2 size)
    : origin{origin}, size{size}
{
}

Rect2::Rect2(float x, float y, float w, float h)
    : Rect2(Vec2(x, y), Vec2(w, h))
{
}

Rect2::Rect2()
    : Rect2{Vec2(0, 0), Vec2(0, 0)}
{
}

Vec2 Rect2::half_size() const
{
    return Vec2(size.x / 2, size.y / 2);
}

Vec2 Rect2::center() const
{
    return Vec2(origin.x + size.x / 2, origin.y + size.y / 2);
}

float Rect2::left() const
{
    return origin.x;
}

float Rect2::right() const
{
    return origin.x + size.x;
}

float Rect2::top() const
{
    return origin.y;
}

float Rect2::bottom() const
{
    return origin.y + size.y;
}

std::ostream &operator<<(std::ostream &stream, const Rect2 &rect)
{
    stream << "(x: " << rect.origin.x << ", y: " << rect.origin.y << ", w: " << rect.size.x << ", h:" << rect.size.y << ")";
    return stream;
}

bool Rect2::contains(Vec2 position) const
{
    return left() <= position.x &&
           position.x <= this->right() &&
           top() <= position.y &&
           position.y <= bottom();
}
