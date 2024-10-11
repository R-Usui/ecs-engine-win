#ifndef SCENE_Collision_HPP
#define SCENE_Collision_HPP

#include "Scene.hpp"
#include "Grobal.hpp"
#include "Vec2.hpp"

template <typename T>
static T clamp(T value, T min, T max)
{
    if (value < min)
    {
        return min;
    }
    else if (max < value)
    {
        return max;
    }
    else
    {
        return value;
    }
}

template <typename T>
static T is_positive(T value)
{
    return 0 <= value;
}

class SceneCollision : public Scene
{
private:
    const float delta = 1e-8;

    void _spawn_help_label()
    {
        auto e = entity_manager.add_entity("label");

        e->add_component<CTransform>(Vec2(0, 0));
        e->get_component<CTransform>()->will_ignore_camera_position = true;

        e->add_component<CText>("SceneCollsion.hpp (Press Shift+M to return home scene)", "mario", 18);
    }

    void sys_change_scene()
    {
        if ((Grobal::button_input_manager.is_pressed("lshift") || Grobal::button_input_manager.is_pressed("rshift")) &&
            Grobal::button_input_manager.has_triggered("M"))
        {
            should_end = true;
            next_scene_key = "main";
        }
    }

    void sys_debug()
    {
    }

public:
    SceneCollision()
    {
    }

    void call_sub_systems() override
    {
        sys_change_scene();
    }

    void register_asset() override
    {
        std::cout << "SceneCollision::register_asset() called" << std::endl;

        Grobal::font_manager.add("mario", "mario.ttf");
    }

    void register_input() override
    {
        std::cout << "SceneCollision::register_input() called" << std::endl;

        Grobal::button_input_manager.add("LCLICK", KeyInputSource::MOUSE, sf::Mouse::Left);

        Grobal::button_input_manager.add("ENTER", KeyInputSource::KEYBOARD, sf::Keyboard::Enter);
        Grobal::button_input_manager.add("SPACE", KeyInputSource::KEYBOARD, sf::Keyboard::Space);
        Grobal::button_input_manager.add("BS", KeyInputSource::KEYBOARD, sf::Keyboard::BackSpace);
        Grobal::button_input_manager.add("ESCAPE", KeyInputSource::KEYBOARD, sf::Keyboard::Escape);

        Grobal::button_input_manager.add("UP", KeyInputSource::KEYBOARD, sf::Keyboard::Up);
        Grobal::button_input_manager.add("DOWN", KeyInputSource::KEYBOARD, sf::Keyboard::Down);
        Grobal::button_input_manager.add("LEFT", KeyInputSource::KEYBOARD, sf::Keyboard::Left);
        Grobal::button_input_manager.add("RIGHT", KeyInputSource::KEYBOARD, sf::Keyboard::Right);

        Grobal::button_input_manager.add("M", KeyInputSource::KEYBOARD, sf::Keyboard::M);
        Grobal::button_input_manager.add("lshift", KeyInputSource::KEYBOARD, sf::Keyboard::LShift);
        Grobal::button_input_manager.add("rshift", KeyInputSource::KEYBOARD, sf::Keyboard::RShift);
    }

    void when_start() override
    {
        std::cout << "SceneCollision::when_start() called" << std::endl;

        _spawn_help_label();

        sys_debug();

        count = 0;
    }

    void when_end() override
    {
        std::cout << "SceneCollision::when_end() called" << std::endl;

        entity_manager.delete_entities();
    }
};

#endif