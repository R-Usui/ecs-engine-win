#ifndef GROBAL_HPP
#define GROBAL_HPP

#include <string>

#include "Vec2.hpp"
#include "AssetManager.hpp"
#include "SceneManager.hpp"
#include "KeyInputManager.hpp"
#include "CursorInputManager.hpp"

class Grobal
{
public:
    static const Vec2 window_size;
    static const std::string window_tytle;

    static TextureManager texture_manager;
    static FontManager font_manager;

    static SceneManager scene_manager;

    static KeyInputManager button_input_manager;
    static CursorInputManager cursor_input_manager;
};

#endif