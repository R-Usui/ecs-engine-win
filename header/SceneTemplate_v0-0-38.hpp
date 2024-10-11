#ifndef SCENE_TEMPLATE_HPP
#define SCENE_TEMPLATE_HPP

#include "Scene.hpp"
#include "Grobal.hpp"

class SceneTemplate_v0_0_38 : public Scene
{
private:
    const std::string help_text = "SceneTemplate.hpp (Press Shift+M to return home scene)";

    void _spawn_help_label()
    {
        auto e = entity_manager.add_entity("label");

        e->add_component<CTransform>(Vec2(0, 0));
        e->get_component<CTransform>()->will_ignore_camera_position = true;

        e->add_component<CText>(help_text, "mario", 18);
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

public:
    SceneTemplate_v0_0_38()
    {
    }

    void call_sub_systems() override
    {
        sys_change_scene();
    }

    void register_asset() override
    {
        Grobal::font_manager.add("mario", "mario.ttf");
    }

    void register_input() override
    {
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
        _spawn_help_label();

        count = 0;
    }

    void when_end() override
    {
        entity_manager.delete_entities();
    }
};

#endif