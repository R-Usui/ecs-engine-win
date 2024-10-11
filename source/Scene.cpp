#include <memory>
#include <map>

#include "Scene.hpp"
#include "Grobal.hpp"

void Scene::update(sf::RenderWindow &window)
{
    entity_manager.update();

    call_sub_systems();
    sys_render(window);

    if (!is_paused)
    {
        ++count;
    }
}

void Scene::_render_text(sf::RenderWindow &window, std::shared_ptr<Entity> entity)
{
    auto c_text = entity->get_component<CText>();
    auto c_transform = entity->get_component<CTransform>();

    if (!c_text || !c_transform)
    {
        return;
    }

    sf::Text render_target;

    // position
    Vec2 position;
    if (c_transform->will_ignore_camera_position)
    {
        position = c_transform->position;
    }
    else
    {
        position = c_transform->position - camera_position;
    }
    render_target.setPosition(position);

    // rotation
    render_target.setRotation(c_transform->angle);

    // string
    render_target.setString(c_text->string);

    // font
    auto font = Grobal::font_manager.get(c_text->font_key);
    render_target.setFont(*font);

    // character size
    render_target.setCharacterSize(c_text->font_size);

    // origin
    auto bound_size = render_target.getLocalBounds();

    auto origin = Vec2(c_text->offset.x * bound_size.width,
                       c_text->offset.y * bound_size.height);
    render_target.setOrigin(origin);

    // color
    render_target.setFillColor(c_text->fill_color);
    render_target.setOutlineColor(c_text->line_color);

    // outline width
    render_target.setOutlineThickness(c_text->line_width);

    window.draw(render_target);
}

void Scene::_render_sprite(sf::RenderWindow &window, std::shared_ptr<Entity> entity)
{
    auto c_sprite = entity->get_component<CSprite>();
    auto c_transform = entity->get_component<CTransform>();

    if (!c_sprite || !c_transform)
    {
        return;
    }

    sf::Sprite render_target;

    // position
    Vec2 position;
    if (c_transform->will_ignore_camera_position)
    {
        position = c_transform->position;
    }
    else
    {
        position = c_transform->position - camera_position;
    }
    render_target.setPosition(position);

    // rotation
    render_target.setRotation(c_transform->angle);

    // origin
    auto origin = Vec2(c_sprite->offset.x * c_sprite->texture_rect.size.x,
                       c_sprite->offset.y * c_sprite->texture_rect.size.y);
    render_target.setOrigin(origin);

    // texture
    auto texture_key = c_sprite->texture_key;
    auto texture = Grobal::texture_manager.get(texture_key);
    render_target.setTexture(*texture);

    // scale
    auto rect = c_sprite->texture_rect;
    render_target.setTextureRect(sf::IntRect(rect.origin.x, rect.origin.y, rect.size.x, rect.size.y));

    render_target.setScale(c_sprite->size.x / c_sprite->texture_rect.size.x,
                           c_sprite->size.y / c_sprite->texture_rect.size.y);

    window.draw(render_target);
}

void Scene::_render_rect(sf::RenderWindow &window, std::shared_ptr<Entity> entity)
{
    auto c_rect = entity->get_component<CShapeRect>();
    auto c_transform = entity->get_component<CTransform>();

    if (!c_rect || !c_transform)
    {
        return;
    }

    sf::RectangleShape render_target;

    // position
    Vec2 position;
    if (c_transform->will_ignore_camera_position)
    {
        position = c_transform->position;
    }
    else
    {
        position = c_transform->position - camera_position;
    }
    render_target.setPosition(position);

    // rotation
    render_target.setRotation(c_transform->angle);

    // size
    render_target.setSize(c_rect->size);

    // origin
    auto origin = Vec2(c_rect->offset.x * c_rect->size.x,
                       c_rect->offset.y * c_rect->size.y);
    render_target.setOrigin(origin);

    // color
    render_target.setFillColor(c_rect->fill_color);
    render_target.setOutlineColor(c_rect->line_color);

    // outline width
    render_target.setOutlineThickness(c_rect->line_width);

    window.draw(render_target);
}

void Scene::_render(sf::RenderWindow &window, std::shared_ptr<Entity> entity)
{
    auto c_transform = entity->get_component<CTransform>();

    auto c_sprite = entity->get_component<CSprite>();
    if (c_sprite && c_transform)
    {
        _render_sprite(window, entity);
    }

    auto c_shape_rect = entity->get_component<CShapeRect>();
    if (c_shape_rect && c_transform)
    {
        _render_rect(window, entity);
    }

    auto c_text = entity->get_component<CText>();
    if (c_text && c_transform)
    {
        _render_text(window, entity);
    }
}

void Scene::sys_render(sf::RenderWindow &window)
{
    window.clear();

    // BACKGROUNDの描画
    for (auto e : entity_manager.get_entities())
    {
        _render(window, e);
    }

    window.display();
}