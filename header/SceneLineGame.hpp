#ifndef SCENE_LINE_GAME_HPP
#define SCENE_LINE_GAME_HPP

#include "Scene.hpp"
#include "Grobal.hpp"

#include "CursorInputManager.hpp"

#include "Vec2.hpp"
#include "Rect2.hpp"

/*
>cell_code
 0 1 2
 3 4 5
 6 7 8
*/

class SceneLineGame : public Scene
{
private:
    const int rows_init = 3;
    const int colomns_init = 3;

    const int rows_min = 2;
    const int colomns_min = 2;

    const int rows_max = 20;
    const int colomns_max = 20;

    int rows = rows_init;
    int colomns = colomns_init;

    int current_side = 1;

    int cell_edge_size()
    {
        return std::min(Grobal::window_size.x / colomns, Grobal::window_size.y / rows) * 0.9;
    }

    Vec2 cell_size()
    {
        return Vec2(cell_edge_size(), cell_edge_size());
    }

    Vec2 field_size()
    {
        return Vec2(cell_size().x * colomns, cell_size().y * rows);
    }

    int cell_code(int row, int colomn)
    {
        return colomn * row + colomn;
    }

    Vec2 cell_matrix(int cell_code)
    {
        return Vec2(cell_code % colomns, cell_code / colomns);
    }

    // center
    Vec2 cell_pos(int cell_code)
    {
        int x = Grobal::window_size.x / 2 - field_size().x / 2 + cell_matrix(cell_code).x * cell_size().x + cell_size().x / 2;
        int y = Grobal::window_size.y / 2 - field_size().y / 2 + cell_matrix(cell_code).y * cell_size().y + cell_size().y / 2;
        return Vec2(x, y);
    }

    //

    const std::string help_text = "SceneLineGame.hpp (Press Shift+M to return to home scene)";

    void _spawn_help_label()
    {
        auto e = entity_manager.add_entity("label");

        e->add_component<CTransform>(Vec2(0, 0));
        e->get_component<CTransform>()->will_ignore_camera_position = true;

        e->add_component<CText>(help_text, "mario", 18);
    }

    //

    void _spawn_frames()
    {
        for (int cell_code = 0; cell_code < rows * colomns; ++cell_code)
        {
            auto e = entity_manager.add_entity("frame");

            // CTransform
            auto position = cell_pos(cell_code);

            e->add_component<CTransform>(position);

            // CShapeRect
            auto size = cell_size();
            e->add_component<CShapeRect>(size, Vec2(0.5, 0.5),
                                         RGBA(0, 255, 0, 0),
                                         RGBA(255, 255, 255, 255), 1);

            // CAttribute
            e->add_component<CAttribute>();
            e->get_component<CAttribute>()->int_map["cell_code"] = cell_code;
            e->get_component<CAttribute>()->int_map["side"] = 0;

            // CBUtton
            e->add_component<CButton>("LCLICK", size, Vec2(0.5, 0.5));

            // CText
            e->add_component<CText>(std::to_string(cell_code), "mario", size.x / 2);
            e->get_component<CText>()->offset = Vec2(0.5, 0.5);
        }
    }

    //

    void sys_change_scene()
    {
        if ((Grobal::button_input_manager.is_pressed("LSHIFT") || Grobal::button_input_manager.is_pressed("rshift")) &&
            Grobal::button_input_manager.has_triggered("M"))
        {
            should_end = true;
            next_scene_key = "main";
        }
    }

    //

    void sys_camera()
    {
        if (!Grobal::button_input_manager.is_pressed("CAMERA"))
        {
            return;
        }

        float speed = 3.0f;

        if (Grobal::button_input_manager.is_pressed("RESET"))
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

    //

    Rect2 _get_Rect(Vec2 origin, Vec2 size, Vec2 offset)
    {
        float x = origin.x - size.x * offset.x;
        float y = origin.y - size.y * offset.y;
        float w = size.x;
        float h = size.y;

        return Rect2(x, y, w, h);
    }
    //

    void sys_button()
    {
        auto cursor_position = Grobal::cursor_input_manager.get_current_position();
        auto camera_position = this->camera_position;

        for (auto e : entity_manager.get_entities())
        {

            // 1. 対象エンティティの決定

            auto c_transform = e->get_component<CTransform>();
            auto c_button = e->get_component<CButton>();

            if (!c_transform || !c_button)
            {
                continue;
            }

            // 2. カーソルが乗っているかの判定

            auto button_rect = _get_Rect(c_transform->position, c_button->size, c_button->offset);
            auto relative_cursor_position = camera_position + cursor_position;

            if (button_rect.contains(relative_cursor_position))
            {
                c_button->is_cursor_on = true;
            }
            else
            {
                c_button->is_cursor_on = false;
            }

            // 3. トリガーキー状態の取得

            bool has_triggered = Grobal::button_input_manager.has_triggered(c_button->trigger_key);
            bool is_pressed = Grobal::button_input_manager.is_pressed(c_button->trigger_key);
            bool has_released = Grobal::button_input_manager.has_released(c_button->trigger_key);

            // 3. State遷移

            switch (c_button->state)
            {
            case CButton::State::NONE:
                if (c_button->is_cursor_on)
                {
                    if (has_triggered)
                    {
                        c_button->state = CButton::State::HAS_TRIGGERED;
                    }
                }

                break;

            case CButton::State::HAS_TRIGGERED:

                if (c_button->is_cursor_on)
                {
                    if (is_pressed)
                    {
                        c_button->state = CButton::State::IS_PRESSED;
                    }
                    else if (has_released)
                    {
                        c_button->state = CButton::State::HAS_RELEASED;
                    }
                }
                else
                {
                    c_button->state = CButton::State::HAS_CANCELED;
                }

                break;

            case CButton::State::IS_PRESSED:

                if (c_button->is_cursor_on)
                {
                    if (has_released)
                    {
                        c_button->state = CButton::State::HAS_RELEASED;
                    }
                }
                else
                {
                    c_button->state = CButton::State::HAS_CANCELED;
                }

                break;

            case CButton::State::HAS_RELEASED:

                if (c_button->is_cursor_on)
                {
                    if (has_triggered)
                    {
                        c_button->state = CButton::State::HAS_TRIGGERED;
                    }
                    else if (is_pressed)
                    {
                        c_button->state = CButton::State::HAS_TRIGGERED;
                    }
                    else if (has_released)
                    {
                    }
                    else
                    {
                        c_button->state = CButton::State::NONE;
                    }
                }
                else
                {
                    c_button->state = CButton::State::NONE;
                }

                break;

            case CButton::State::HAS_CANCELED:

                if (c_button->is_cursor_on)
                {
                    if (has_triggered)
                    {
                        c_button->state = CButton::State::HAS_TRIGGERED;
                    }
                    else if (is_pressed)
                    {
                        c_button->state = CButton::State::HAS_TRIGGERED;
                    }
                }
                else
                {
                    c_button->state = CButton::State::NONE;
                }

                break;
            }
        }
    }

    //

    void _change_field_size(int rows_new, int colomns_new)
    {
        int rows_memory = rows;
        int colomns_memory = colomns;

        rows = rows_new;
        colomns = colomns_new;

        rows = std::max(rows_min, rows);
        colomns = std::max(colomns_min, colomns);

        rows = std::min(rows_max, rows);
        colomns = std::min(colomns_max, colomns);

        // if (rows != rows_memory || colomns != colomns_memory)
        //{
        entity_manager.delete_entities("frame");
        _spawn_frames();
        //}
    }

    void sys_change_field_size()
    {
        if (!Grobal::button_input_manager.is_pressed("FIELD"))
        {
            return;
        }

        if (Grobal::button_input_manager.has_released("UP"))
        {
            _change_field_size(rows - 1, colomns);
        }
        if (Grobal::button_input_manager.has_released("DOWN"))
        {
            _change_field_size(rows + 1, colomns);
        }
        if (Grobal::button_input_manager.has_released("LEFT"))
        {
            _change_field_size(rows, colomns - 1);
        }
        if (Grobal::button_input_manager.has_released("RIGHT"))
        {
            _change_field_size(rows, colomns + 1);
        }
        if (Grobal::button_input_manager.has_triggered("RESET"))
        {
            _change_field_size(rows_init, colomns_init);
        }
    }

    //

    void _when_cursor_is_on(std::shared_ptr<Entity> e)
    {
        auto c_button = e->get_component<CButton>();
        auto c_rect = e->get_component<CShapeRect>();

        if (!c_button || !c_rect)
        {
            return;
        }

        // カーソルが乗っている時フレームを赤に
        if (c_button->is_cursor_on)
        {
            c_rect->line_color = RGBA(255, 0, 0, 255);
        }
        else
        {
            c_rect->line_color = RGBA(255, 255, 255, 255);
        }
    }

    void _frame_button_resolution(std::shared_ptr<Entity> e)
    {
        auto c_button = e->get_component<CButton>();
        auto c_rect = e->get_component<CShapeRect>();
        auto c_attr = e->get_component<CAttribute>();

        if (!c_button || !c_rect || !c_attr)
        {
            return;
        }

        if (c_button->state == CButton::State::HAS_TRIGGERED)
        {
            c_rect->size *= 95.0f / 100.0f;
        }
        else if (c_button->state == CButton::State::IS_PRESSED)
        {
                }
        else if (c_button->state == CButton::State::HAS_RELEASED)
        {
            // change size
            c_rect->size *= 100.0f / 95.0f;

            // change fill color

            auto &side = c_attr->int_map["side"];
            if (side == 0 && current_side == 1)
            {
                side = 1;
                current_side = 2;
                c_rect->fill_color = RGBA(0, 0, 255, 155);
            }
            else if (side == 0 && current_side == 2)
            {
                side = 2;
                current_side = 1;
                c_rect->fill_color = RGBA(255, 0, 0, 155);
            }
        }
        else if (c_button->state == CButton::State::HAS_CANCELED)
        {
            // change size
            c_rect->size *= 100.0f / 95.0f;
        }
    }

    void sys_button_resolution()
    {
        for (auto e : entity_manager.get_entities())
        {
            if (e->get_tag() == "frame")
            {
                _when_cursor_is_on(e);
                _frame_button_resolution(e);
            }
        }
    }

    //

    void call_sub_systems() override
    {

        sys_change_scene();

        sys_camera();

        sys_change_field_size();

        sys_button();

        sys_button_resolution();
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

        Grobal::button_input_manager.add("CAMERA", KeyInputSource::KEYBOARD, sf::Keyboard::C);
        Grobal::button_input_manager.add("FIELD", KeyInputSource::KEYBOARD, sf::Keyboard::F);
        Grobal::button_input_manager.add("RESET", KeyInputSource::KEYBOARD, sf::Keyboard::R);
        Grobal::button_input_manager.add("M", KeyInputSource::KEYBOARD, sf::Keyboard::M);

        Grobal::button_input_manager.add("LSHIFT", KeyInputSource::KEYBOARD, sf::Keyboard::LShift);
        Grobal::button_input_manager.add("RSHIFT", KeyInputSource::KEYBOARD, sf::Keyboard::RShift);
    }

    void when_start() override
    {
        _spawn_help_label();

        _spawn_frames();

        count = 0;

        camera_position = Vec2(0, 0);
    }

    void when_end() override
    {
        entity_manager.delete_entities();
    }
};

#endif