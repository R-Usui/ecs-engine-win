#include "CursorInputManager.hpp"

void CursorInputManager::update(const sf::WindowBase &window)
{
    last_position = current_position;

    auto current_position_temp = sf::Mouse::getPosition(window);
    current_position.x = current_position_temp.x;
    current_position.y = current_position_temp.y;
}

Vec2 CursorInputManager::get_current_position() const
{
    return current_position;
}

Vec2 CursorInputManager::get_vector() const
{
    return last_position - current_position;
}