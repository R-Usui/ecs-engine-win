#ifndef SCENE_Main_HPP
#define SCENE_Main_HPP

#include <vector>
#include <string>

#include "Grobal.hpp"
#include "Component.hpp"
#include "Scene.hpp"

class SceneMain : public Scene
{
private:
    std::vector<std::string> scene_keys()
    {
        return Grobal::scene_manager.get_all_keys();
    }

    int number_scene_keys()
    {
        return scene_keys().size();
    }

    // ZERO origin
    int selected_index = 0;

    //

    void _spawn_labels()
    {
        int font_size = 18;

        for (int i = 0; i < number_scene_keys(); ++i)
        {
            auto e = entity_manager.add_entity("LABEL");
            e->add_component<CTransform>(Vec2(0, i * font_size));

            e->add_component<CText>(scene_keys()[i], "mario", font_size);

            e->add_component<CAttribute>();
            e->get_component<CAttribute>()->string_map["scene_key"] = scene_keys()[i];
        }
    }

    //

    void sys_select()
    {
        if (Grobal::button_input_manager.has_triggered("DOWN"))
        {
            ++selected_index;

            if (number_scene_keys() <= selected_index)
            {
                selected_index = 0;
            }
        }
        else if (Grobal::button_input_manager.has_triggered("UP"))
        {
            --selected_index;

            if (selected_index < 0)
            {
                selected_index = number_scene_keys() - 1;
            }
        }
    }

    //

    void sys_label_color()
    {
        for (auto e : entity_manager.get_entities("LABEL"))
        {
            if (!e->has_component<CAttribute>() || !e->has_component<CText>())
            {
                continue;
            }

            if (e->get_component<CAttribute>()->string_map["scene_key"] == scene_keys()[selected_index])
            {
                e->get_component<CText>()->fill_color = RGBA(255, 0, 0, 255);
                e->get_component<CText>()->string = ">" + e->get_component<CAttribute>()->string_map["scene_key"];
            }
            else
            {
                e->get_component<CText>()->fill_color = RGBA(255, 255, 255, 255);
                e->get_component<CText>()->string = " " + e->get_component<CAttribute>()->string_map["scene_key"];
            }
        }
    }

    //

    void sys_chage_scene()
    {
        if (Grobal::button_input_manager.has_triggered("ENTER"))
        {
            should_end = true;
            next_scene_key = scene_keys()[selected_index];
        }
    }

public:
    SceneMain()
    {
    }

    void call_sub_systems() override
    {
        sys_chage_scene();
        sys_label_color();
        sys_select();
    }

    void register_asset() override
    {
        std::cout << "SceneMain::register_asset() called" << std::endl;

        Grobal::font_manager.add("mario", "mario.ttf");
    }

    void register_input() override
    {
        std::cout << "SceneMain::register_input() called" << std::endl;

        Grobal::button_input_manager.add("ENTER", KeyInputSource::KEYBOARD, sf::Keyboard::Enter);
        Grobal::button_input_manager.add("UP", KeyInputSource::KEYBOARD, sf::Keyboard::Up);
        Grobal::button_input_manager.add("DOWN", KeyInputSource::KEYBOARD, sf::Keyboard::Down);
    }

    void when_start() override
    {
        std::cout << "SceneMain::when_start() called" << std::endl;

        selected_index = 0;

        _spawn_labels();
    }

    void when_end() override
    {
        std::cout << "SceneMain::when_end() called" << std::endl;

        entity_manager.delete_entities();
    }
};

#endif