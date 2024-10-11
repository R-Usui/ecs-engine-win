#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <string>
#include <memory>
#include <vector>
#include <map>

#include "Vec2.hpp"
#include "Rect2.hpp"
#include "RGBA.hpp"
#include "Animation.hpp"

class Component
{
};

class CTransform : public Component
{
public:
    Vec2 position;
    Vec2 velocity;
    Vec2 accel;
    float angle;
    float anglular_velocity = 0.0f;
    float rotational_speed = 0.0f;

    bool will_ignore_camera_position = false;

    CTransform();
    CTransform(Vec2 position,
               Vec2 velocity = Vec2(0.0f, 0.0f),
               Vec2 accel = Vec2(0.0f, 0.0f),
               float angle = 0.0f);
};

class CSprite : public Component
{
public:
    // CAUTION: This is a name registered by TextureManager, not a image name itself.
    std::string texture_key;

    Rect2 texture_rect;

    Vec2 size;

    Vec2 offset = Vec2(0, 0);

    CSprite(std::string texture_key, Rect2 texture_rect, Vec2 size, Vec2 offset = Vec2(0, 0));
};

class CAnimation : public Component
{
    std::map<std::string, Animation> anims;
    std::string current_key;
    int count = 0;

    Animation current_anim() const;

    Vec2 current_grid() const;

public:
    CAnimation() {}

    void add_anim(const std::string &key, Animation anim);
    void set_anim(const std::string &key);
    void add_count();
    void add_count(int amount);

    std::string current_texture_key() const;
    Rect2 current_texture_rect() const;
};

class CShapeRect : public Component
{
public:
    Vec2 size;
    Vec2 offset;
    RGBA line_color;
    RGBA fill_color;
    int line_width;

    CShapeRect(Vec2 size,
               Vec2 offset = Vec2(0, 0),
               RGBA fill_color = RGBA(255, 255, 255, 255),
               RGBA line_color = RGBA(255, 255, 255, 255),
               int line_width = 1);
};

class CText : public Component
{
public:
    std::string string;
    std::string font_key;

    int font_size;

    Vec2 offset = Vec2(0, 0);

    RGBA fill_color;
    RGBA line_color;
    float line_width = 0;

    CText(std::string string, std::string font_key, int font_size)
        : string{string},
          font_key{font_key},
          font_size{font_size}
    {
    }
};

class CLifespan : public Component
{

public:
    int value;

    CLifespan(int value)
        : value{value}
    {
    }
};

class CAttribute : public Component
{
public:
    std::map<std::string, int> int_map;
    std::map<std::string, std::string> string_map;
};

class CCursorDetector : public Component
{
public:
    CCursorDetector(Vec2 size, Vec2 offset);

    Vec2 size;
    Vec2 offset;

    bool is_cursor_on = false;
};

class CButton : public Component
{
public:
    enum class State
    {
        NONE,
        HAS_TRIGGERED,
        IS_PRESSED,
        HAS_RELEASED,
        HAS_CANCELED,
    };

    CButton(std::string trigger_key, Vec2 size, Vec2 offset);

    std::string trigger_key;
    Vec2 size;
    Vec2 offset;

    bool is_cursor_on = false;

    State state = State::NONE;
};

#endif