#include <SFML/System/Clock.hpp>

#include "Engine.hpp"

#include "SceneMain.hpp"
#include "SceneTest3.hpp"
#include "SceneLineGame.hpp"
#include "SceneRPG.hpp"
#include "SceneTemplate_v0-0-38.hpp"

void Engine::_init_window()
{
    sf::VideoMode mode = sf::VideoMode(Grobal::window_size.x, Grobal::window_size.y);
    auto tytle = Grobal::window_tytle;
    auto style = sf::Style::Close;

    window.create(mode, tytle, style);

    window.setFramerateLimit(60);
}

void Engine::_init_scene_manager()
{
    Grobal::scene_manager.add<SceneMain>("main");
    Grobal::scene_manager.add<SceneTest3>("test3");
    Grobal::scene_manager.add<SceneLineGame>("line_game");
    Grobal::scene_manager.add<SceneRPG>("rpg");
    Grobal::scene_manager.add<SceneTemplate_v0_0_38>("template");

    Grobal::scene_manager.set("main");
}

void Engine::start_scene()
{
    auto current_scene = Grobal::scene_manager.get_current_scene();

    current_scene->register_asset();
    current_scene->register_input();

    current_scene->should_end = false;

    current_scene->when_start();
}

void Engine::end_scene()
{
    auto current_scene = Grobal::scene_manager.get_current_scene();

    current_scene->when_end();

    Grobal::texture_manager.delete_all();
    Grobal::font_manager.delete_all();

    Grobal::button_input_manager.delete_all();
}

Engine::Engine()
{
    _init_window();
    _init_scene_manager();
}

void Engine::run()
{
    start_scene();

    while (window.isOpen())
    {

        // 1. Event処理
        // (Closeボタンでアプリ終了)
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
        }

        // 2. Inputをアップデート
        Grobal::button_input_manager.update();
        Grobal::cursor_input_manager.update(window);

        // 3. Sceneに関する処理
        auto current_scene = Grobal::scene_manager.get_current_scene();
        if (current_scene->should_end)
        {
            end_scene();

            Grobal::scene_manager.set(current_scene->next_scene_key);

            start_scene();
        }
        else
        {
            Grobal::scene_manager.get_current_scene()->update(window);
        }
    }

    end_scene();
}
