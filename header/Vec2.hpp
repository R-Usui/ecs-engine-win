#ifndef VEC2_HPP
#define VEC2_HPP

#include <ostream>
#include <cmath>
#include <string>

#include <SFML/System/Vector2.hpp>

class Vec2
{
public:
    float x = 0;
    float y = 0;

    Vec2();
    Vec2(float x, float y);

    bool operator==(const Vec2 &rhs) const;
    bool operator!=(const Vec2 &rhs) const;

    Vec2 operator+(const Vec2 &rhs) const;
    Vec2 operator-(const Vec2 &rhs) const;
    Vec2 operator/(float value) const;
    Vec2 operator*(float value) const;

    void operator+=(const Vec2 &rhs);
    void operator-=(const Vec2 &rhs);
    void operator/=(float value);
    void operator*=(float value);

    operator sf::Vector2f();
    operator std::string();

    friend std::ostream &
    operator<<(std::ostream &stream, const Vec2 &vec);

    float length() const;
    float dist(const Vec2 &rhs) const;
    void norm();
    void rotate(float degree);
};

#endif // VEC2_HPP