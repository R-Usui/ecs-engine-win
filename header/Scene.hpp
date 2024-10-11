#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include "EntityManager.hpp"

class Scene
{
private:
    void _render_text(sf::RenderWindow &window, std::shared_ptr<Entity> entity);
    void _render_sprite(sf::RenderWindow &window, std::shared_ptr<Entity> entity);
    void _render_rect(sf::RenderWindow &window, std::shared_ptr<Entity> entity);
    void _render(sf::RenderWindow &window, std::shared_ptr<Entity> entity);

    void sys_render(sf::RenderWindow &window);

protected:
    EntityManager entity_manager;
    bool is_paused = false;
    int count = 0;

    Vec2 camera_position = Vec2(0, 0);

    virtual void call_sub_systems() = 0;

public:
    bool should_end = false;
    std::string next_scene_key;

    void update(sf::RenderWindow &window);

    virtual void register_asset() = 0;
    virtual void register_input() = 0;

    virtual void when_start() = 0;
    virtual void when_end() = 0;
};

#endif