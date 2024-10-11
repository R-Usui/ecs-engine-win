#include <numbers>

#include "Vec2.hpp"

Vec2::Vec2()
    : x{0},
      y{0}
{
}

Vec2::Vec2(float x, float y)
    : x{x},
      y{y}
{
}

bool Vec2::operator==(const Vec2 &rhs) const
{
    return (x == rhs.x) && (y == rhs.y);
}

bool Vec2::operator!=(const Vec2 &rhs) const
{
    return !(*this == rhs);
}

Vec2 Vec2::operator+(const Vec2 &rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2 &rhs) const
{
    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator/(float value) const
{
    return Vec2(x / value, y / value);
}

Vec2 Vec2::operator*(float value) const
{
    return Vec2(x * value, y * value);
}

void Vec2::operator+=(const Vec2 &rhs)
{
    *this = *this + rhs;
}

void Vec2::operator-=(const Vec2 &rhs)
{
    *this = *this - rhs;
}

void Vec2::operator/=(float value)
{
    *this = *this / value;
}

void Vec2::operator*=(float value)
{
    *this = *this * value;
}

Vec2::operator sf::Vector2f()
{
    return sf::Vector2f(x, y);
}

Vec2::operator std::string()
{
    return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
}

std::ostream &operator<<(std::ostream &stream, const Vec2 &vec)
{
    stream << "(" << vec.x << "," << vec.y << ")";
    return stream;
}

float Vec2::length() const
{
    return sqrt(x * x + y * y);
}

float Vec2::dist(const Vec2 &rhs) const
{
    return (*this - rhs).length();
}

void Vec2::norm()
{
    if (length() != 0)
    {
        *this /= length();
    }
}

void Vec2::rotate(float degree)
{
    auto pi = std::numbers::pi;
    auto radian = degree * pi / 180;

    auto x_temp = std::cos(radian) * x - std::sin(radian) * y;
    auto y_temp = std::sin(radian) * x + std::cos(radian) * y;

    x = x_temp;
    y = y_temp;
}