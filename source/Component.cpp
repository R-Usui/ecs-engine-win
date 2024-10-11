#include "Component.hpp"

// CTransform

CTransform::CTransform(Vec2 position,
                       Vec2 velocity,
                       Vec2 accel,
                       float angle)
    : position{position},
      velocity{velocity},
      accel{accel},
      angle{angle}
{
}

CTransform::CTransform()
    : CTransform(Vec2(0, 0))
{
}

// CSprite

CSprite::CSprite(std::string texture_key,
                 Rect2 texture_rect,
                 Vec2 size, Vec2 offset)
    : texture_key{texture_key},
      texture_rect{texture_rect}, size{size}, offset{offset}
{
}

// CAnimation

Animation CAnimation::current_anim() const
{
    auto target = anims.find(current_key);

    if (target == anims.end())
    {
        throw std::invalid_argument("KEY NOT FOUND (unfound key = " + current_key + ")");
    }

    return target->second;
}

Vec2 CAnimation::current_grid() const
{
    // 何枚目のフレームを表示するべきか (最初=0)
    int frame_count;
    if (current_anim().will_zigzag)
    {
        frame_count = abs(((count / current_anim().duration) % (2 * current_anim().frames_total - 2)) - (current_anim().frames_total - 1));
    }
    else
    {
        frame_count = count / current_anim().duration % current_anim().frames_total;
    }
    frame_count += current_anim().frame_offset;

    int grid_x = frame_count % current_anim().frames_colomn;
    int grid_y = frame_count / current_anim().frames_colomn;

    return Vec2(grid_x, grid_y);
}

void CAnimation::add_anim(const std::string &key, Animation anim)
{
    auto result = anims.insert(std::make_pair(key, anim));

    // 既にkeyが存在しており、挿入に失敗した時の処理
    if (!result.second)
    {
        result.first->second = anim;
    }
}

void CAnimation::set_anim(const std::string &key)
{
    if (anims.find(key) == anims.end())
    {
        throw std::invalid_argument("KEY NOT FOUND (unfound key = " + key + ")");
    }

    current_key = key;
}

void CAnimation::add_count()
{
    ++count;
}

void CAnimation::add_count(int amount)
{
    count += amount;
}

std::string CAnimation::current_texture_key() const
{
    return current_anim().texture_key;
}

Rect2 CAnimation::current_texture_rect() const
{
    int x = current_anim().frame_size.x * current_grid().x;
    int y = current_anim().frame_size.y * current_grid().y;
    int w = current_anim().frame_size.x;
    int h = current_anim().frame_size.y;

    return Rect2(x, y, w, h);
}

// CShapeRect

CShapeRect::CShapeRect(Vec2 size,
                       Vec2 offset,
                       RGBA fill_color,
                       RGBA line_color,
                       int line_width)
    : size{size}, offset{offset},
      fill_color{fill_color},
      line_color{line_color},
      line_width{line_width}
{
}

CCursorDetector::CCursorDetector(Vec2 size,
                                 Vec2 offset = Vec2(0, 0))
    : size{size}, offset{offset}
{
}

CButton::CButton(std::string trigger_key,
                 Vec2 size,
                 Vec2 offset = Vec2(0, 0))
    : trigger_key{trigger_key}, size{size}, offset{offset}
{
}