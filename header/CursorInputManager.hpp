#ifndef CURSOR_INPUT_MANAGER_HPP
#define CURSOR_INPUT_MANAGER_HPP

#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Vec2.hpp"

class CursorInputManager
{
    Vec2 current_position;
    Vec2 last_position;

public:
    void update(const sf::WindowBase &window);

    Vec2 get_current_position() const;

    Vec2 get_vector() const;
};

#endif
