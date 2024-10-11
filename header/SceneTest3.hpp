#ifndef SCENE_TEST3_HPP
#define SCENE_TEST3_HPP

#include "Scene.hpp"
#include "Grobal.hpp"
#include "AssetManager.hpp"

class SceneTest3 : public Scene
{
private:
    TagType tag_label = "LABEL";
    TagType tag_box = "BOX";
    TagType tag_flower = "FLOWER";
    TagType tag_dot = "DOT";
    TagType tag_center_marker = "CENTER";

    std::string scene_name = "Project title: MyECS+SFML2 v0-0-29\nScene name : SceneTest3";

    std::shared_ptr<Entity> label;
    const int font_size_min = 18;
    const int font_size_max = 30;
    int font_size = font_size_min;

    //

    void _spawn_center_marker()
    {
        auto e = entity_manager.add_entity(tag_center_marker);

        // CTransform
        e->add_component<CTransform>(Grobal::window_size / 2.0);

        // CShapeRect
        auto size = Vec2(3, 3);
        e->add_component<CShapeRect>(size);
    }

    void _spawn_scene_label()
    {
        auto e = entity_manager.add_entity(tag_label);

        e->add_component<CTransform>(Vec2(0, 0));
        e->get_component<CTransform>()->will_ignore_camera_position = true;

        e->add_component<CText>(scene_name, "mario", font_size);

        label = e;
    }

    void _spawn_box_toward(Vec2 destination)
    {
        auto e = entity_manager.add_entity(tag_box);

        // CTransform
        auto position = Grobal::window_size / 2.0;

        auto velocity = destination - Grobal::window_size / 2.0;
        velocity /= 250;

        e->add_component<CTransform>(position, velocity);

        // CShapeRect
        auto size = Vec2(128, 128);
        e->add_component<CShapeRect>(size, Vec2(0.5, 0.5),
                                     RGBA(0, 0, 0, 0),
                                     RGBA(255, 255, 255, 255), 3);

        // CSprite
        auto texture_key = "slime9";
        auto texture_size = Grobal::texture_manager.get(texture_key)->getSize();
        e->add_component<CSprite>("slime",
                                  Rect2(Vec2(0, 0), Vec2(texture_size.x / 3, texture_size.y / 3)),
                                  size,
                                  Vec2(0.5, 0.5));

        // CAnimation
        Animation anim_down = Animation(texture_key, 10, Vec2(texture_size.x / 3, texture_size.y / 3), 3, 3, 0, true);
        Animation anim_right = Animation(texture_key, 3, Vec2(texture_size.x / 3, texture_size.y / 3), 3, 3, 3, true);
        Animation anim_up = Animation(texture_key, 10, Vec2(texture_size.x / 3, texture_size.y / 3), 3, 3, 6, true);

        e->add_component<CAnimation>();
        e->get_component<CAnimation>()->add_anim("down", anim_down);
        e->get_component<CAnimation>()->add_anim("right", anim_right);
        e->get_component<CAnimation>()->add_anim("up", anim_up);
    }

    void _spawn_flower_at(Vec2 origin = Grobal::window_size / 2.0)
    {
        int number_box = 2 + rand() % 10;
        int angle_offset = rand() % 360;
        int velocity_rand = rand() % 4;
        int ratational_speed_rand = rand() % 10;
        int angular_velocity_rand = rand() % 2;

        for (int i = 0; i < number_box; ++i)
        {
            auto e = entity_manager.add_entity(tag_flower);

            // CTransform
            auto position = origin;

            auto velocity = Vec2(1 + velocity_rand, 0);

            auto angle = 360.0f / float(number_box) * float(i) + angle_offset;
            velocity.rotate(angle);

            auto accel = Vec2(0, 0);

            e->add_component<CTransform>(position, velocity, accel);

            e->get_component<CTransform>()->rotational_speed = 30 + ratational_speed_rand;

            e->get_component<CTransform>()->anglular_velocity = 1 + angular_velocity_rand;

            // CShapeRect
            auto size = Vec2(20, 20);
            e->add_component<CShapeRect>(size, Vec2(0.5, 0.5),
                                         RGBA::random(),
                                         RGBA::white(), 3);

            // CLifespan
            e->add_component<CLifespan>(600);
        }
    }

    void _spawn_dot_at(std::shared_ptr<Entity> ref_entity)
    {
        auto e = entity_manager.add_entity(tag_dot);

        // CTransform
        auto position = ref_entity->get_component<CTransform>()->position;

        e->add_component<CTransform>(position);

        e->get_component<CTransform>()->rotational_speed = 6;

        // CShapeRect
        auto size = Vec2(7, 7);
        auto color = ref_entity->get_component<CShapeRect>()->fill_color;

        e->add_component<CShapeRect>(size, Vec2(0.5, 0.5),
                                     color,
                                     RGBA::white(), 1);

        // CLifespan
        e->add_component<CLifespan>(40);
    }

    void sys_spawn()
    {
        if (Grobal::button_input_manager.has_triggered("BOX"))
        {
            _spawn_box_toward(Grobal::cursor_input_manager.get_current_position() + camera_position);
        }

        if (Grobal::button_input_manager.has_triggered("OK"))
        {
            _spawn_flower_at(Grobal::cursor_input_manager.get_current_position() + camera_position);
        }

        if (count % 5 == 0)
        {
            for (auto ref_e : entity_manager.get_entities(tag_flower))
            {
                _spawn_dot_at(ref_e);
            }
        }

        /*
        if (count % 300 == 0)
        {
            _spawn_flower_at(camera_position + Grobal::window_size / 2);
        }
        */
    }

    //

    bool _is_outside_window(Vec2 origin, Vec2 size)
    {
        auto left = origin.x - camera_position.x;
        auto top = origin.y - camera_position.y;
        auto right = left + size.x;
        auto bottom = top + size.y;

        return Grobal::window_size.x < right ||
               Grobal::window_size.y < bottom ||
               left < 0 ||
               top < 0;
    }

    bool _is_near_cursor(std::shared_ptr<Entity> entity)
    {
        if (!entity->has_component<CTransform>())
        {
            return false;
        }

        auto entity_position = entity->get_component<CTransform>()->position;
        auto cursor_position = Grobal::cursor_input_manager.get_current_position();

        entity_position -= camera_position;

        return entity_position.dist(cursor_position) < 100;
    }

    void _kill_entity_outside_window()
    {
        for (auto e : entity_manager.get_entities(tag_box))
        {
            auto c_transform = e->get_component<CTransform>();
            auto c_rect = e->get_component<CShapeRect>();

            if (!c_transform || !c_rect)
            {
                continue;
            }

            Vec2 origin = Vec2(c_transform->position.x - c_rect->offset.x * c_rect->size.x,
                               c_transform->position.y - c_rect->offset.y * c_rect->size.y);
            Vec2 size = c_rect->size;

            if (_is_outside_window(origin, size))
            {
                e->kill();
            }
        }
    }

    void _kill_entity_near_cursor()
    {
        for (auto e : entity_manager.get_entities())
        {
            auto c_transform = e->get_component<CTransform>();

            if (_is_near_cursor(e) && e->get_tag() != tag_label)
            {
                e->kill();
            }
        }
    }

    void sys_kill()
    {
        _kill_entity_outside_window();

        if (Grobal::button_input_manager.is_pressed("KILL"))
        {
            _kill_entity_near_cursor();
        }

        entity_manager.delete_dead_entities();
    }

    //

    void sys_lifespan()
    {

        for (auto e : entity_manager.get_entities())
        {
            auto c_lifespan = e->get_component<CLifespan>();

            if (!c_lifespan)
            {
                continue;
            }

            if (c_lifespan->value <= 0)
            {
                e->kill();
            }

            c_lifespan->value -= 1;
        }
    }

    //

    void sys_movement()
    {
        for (auto e : entity_manager.get_entities())
        {
            auto c_transform = e->get_component<CTransform>();
            if (!c_transform)
            {
                continue;
            }

            c_transform->velocity += c_transform->accel;
            c_transform->velocity.rotate(c_transform->anglular_velocity);

            c_transform->position += c_transform->velocity;

            c_transform->angle += c_transform->rotational_speed;
        }
    }

    //

    void sys_animation(int speed = 1)
    {
        for (auto e : entity_manager.get_entities(tag_box))
        {

            auto c_transform = e->get_component<CTransform>();
            auto c_anim = e->get_component<CAnimation>();
            auto c_sprite = e->get_component<CSprite>();
            if (!c_transform || !c_anim || !c_sprite)
            {
                continue;
            }

            if (e->get_component<CTransform>()->velocity.y <= 0)
            {
                c_anim->set_anim("up");
            }
            else if (e->get_component<CTransform>()->velocity.y > 0)
            {
                if (e->get_component<CTransform>()->velocity.y < e->get_component<CTransform>()->velocity.x)
                {
                    c_anim->set_anim("right");
                }
                else
                {
                    c_anim->set_anim("down");
                }
            }

            c_sprite->texture_key = c_anim->current_texture_key();
            c_sprite->texture_rect = c_anim->current_texture_rect();

            c_anim->add_count(speed);
        }
    }

    //

    void sys_change_scene()
    {
        if ((Grobal::button_input_manager.is_pressed("lshift") || Grobal::button_input_manager.is_pressed("rshift")) &&
            Grobal::button_input_manager.has_triggered("M"))
        {
            should_end = true;
            next_scene_key = "main";
        }
    }

    //

    void _set_label_text()
    {
        if (!label)
        {
            return;
        }

        if (!label->has_component<CText>())
        {
            return;
        }

        auto &string = label->get_component<CText>()->string;

        //

        string = scene_name;

        //

        string += "\n\n[Input]";
        string += "\n [C]+[Up/Down/Left/Right] : move camera";
        string += "\n [SHIFT]+[C] : reset camera position";
        string += "\n [L]+[Up/Down] : change label size";
        string += "\n [SPACE] / [LEFT CLICK] : spawn flower";
        string += "\n [B] : spawn box";
        string += "\n [K] : kill entities";
        string += "\n [SHIFT]+[M] : go back to main scene";

        //

        string += "\n";

        for (auto tag : {tag_box, tag_dot, tag_flower, tag_label})
        {
            auto count = entity_manager.get_entities(tag).size();

            string += "\nEntity count (tag = " + tag + ") : " + std::to_string(count);
        }

        //

        string += "\n";

        auto &label_font_size = label->get_component<CText>()->font_size;

        string += "\nLabel font size : " + std::to_string(label_font_size);

        if (label_font_size <= font_size_min)
        {
            string += " (MIN)";
        }
        else if (font_size_max <= label_font_size)
        {
            string += " (MAX)";
        }

        string += "\n\nCamera position : ";
        string += camera_position;

        string += "\n\nCount : ";
        string += std::to_string(count);
    }

    void _set_label_size()
    {
        if (!Grobal::button_input_manager.is_pressed("LABEL"))
        {
            return;
        }

        auto &label_font_size = label->get_component<CText>()->font_size;

        if (Grobal::button_input_manager.is_pressed("UP"))
        {
            label_font_size += 1;
        }
        else if (Grobal::button_input_manager.is_pressed("DOWN"))
        {
            label_font_size -= 1;
        }

        label_font_size = label_font_size < font_size_min ? font_size_min : label_font_size;
        label_font_size = font_size_max < label_font_size ? font_size_max : label_font_size;

        font_size = label_font_size;
    }

    void sys_label()
    {
        _set_label_size();
        _set_label_text();
    }

    //

    void sys_camera()
    {
        if (!Grobal::button_input_manager.is_pressed("CAMERA"))
        {
            return;
        }

        float speed = 3.0f;

        if (Grobal::button_input_manager.is_pressed("lshift"))
        {
            camera_position = Vec2(0, 0);
        }
        if (Grobal::button_input_manager.is_pressed("UP"))
        {
            camera_position += Vec2(0, -speed);
        }
        if (Grobal::button_input_manager.is_pressed("DOWN"))
        {
            camera_position += Vec2(0, speed);
        }
        if (Grobal::button_input_manager.is_pressed("LEFT"))
        {
            camera_position += Vec2(-speed, 0);
        }
        if (Grobal::button_input_manager.is_pressed("RIGHT"))
        {
            camera_position += Vec2(speed, 0);
        }
    }

public:
    SceneTest3()
    {
    }

    void call_sub_systems() override
    {
        sys_spawn();

        sys_kill();

        sys_lifespan();

        sys_movement();

        sys_camera();

        sys_animation(1);

        sys_change_scene();

        sys_label();
    }

    void register_asset() override
    {
        std::cout << "SceneTest3::register_asset() called" << std::endl;

        Grobal::texture_manager.add("slime", "slime.png");
        Grobal::texture_manager.add("slime9", "slime9.png");

        Grobal::font_manager.add("mario", "mario.ttf");
    }

    void register_input() override
    {
        std::cout << "SceneTest3::register_input() called" << std::endl;

        Grobal::button_input_manager.add("ENTER", KeyInputSource::KEYBOARD, sf::Keyboard::Enter);

        Grobal::button_input_manager.add("OK", KeyInputSource::KEYBOARD, sf::Keyboard::Space);
        Grobal::button_input_manager.add("OK", KeyInputSource::MOUSE, sf::Mouse::Left);

        Grobal::button_input_manager.add("CANCEL", KeyInputSource::KEYBOARD, sf::Keyboard::BackSpace);

        Grobal::button_input_manager.add("ESCAPE", KeyInputSource::KEYBOARD, sf::Keyboard::Escape);

        Grobal::button_input_manager.add("UP", KeyInputSource::KEYBOARD, sf::Keyboard::Up);
        Grobal::button_input_manager.add("DOWN", KeyInputSource::KEYBOARD, sf::Keyboard::Down);
        Grobal::button_input_manager.add("LEFT", KeyInputSource::KEYBOARD, sf::Keyboard::Left);
        Grobal::button_input_manager.add("RIGHT", KeyInputSource::KEYBOARD, sf::Keyboard::Right);

        Grobal::button_input_manager.add("KILL", KeyInputSource::KEYBOARD, sf::Keyboard::K);
        Grobal::button_input_manager.add("BOX", KeyInputSource::KEYBOARD, sf::Keyboard::B);
        Grobal::button_input_manager.add("CAMERA", KeyInputSource::KEYBOARD, sf::Keyboard::C);

        Grobal::button_input_manager.add("LABEL", KeyInputSource::KEYBOARD, sf::Keyboard::L);

        Grobal::button_input_manager.add("M", KeyInputSource::KEYBOARD, sf::Keyboard::M);
        Grobal::button_input_manager.add("lshift", KeyInputSource::KEYBOARD, sf::Keyboard::LShift);
        Grobal::button_input_manager.add("rshift", KeyInputSource::KEYBOARD, sf::Keyboard::RShift);
    }

    void when_start() override
    {
        std::cout << "SceneTest3::when_start() called" << std::endl;

        _spawn_scene_label();

        _spawn_center_marker();

        camera_position = Vec2(0, 0);

        count = 0;
    }

    void when_end() override
    {
        std::cout << "SceneTest3::when_end() called" << std::endl;

        entity_manager.delete_entities();
    }
};

#endif