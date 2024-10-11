#include "Grobal.hpp"

const Vec2 Grobal::window_size = Vec2(800, 600);

const std::string Grobal::window_tytle = "MyECS+SFML 2";

TextureManager Grobal::texture_manager = TextureManager();

FontManager Grobal::font_manager = FontManager();

SceneManager Grobal::scene_manager = SceneManager();

KeyInputManager Grobal::button_input_manager = KeyInputManager();

CursorInputManager Grobal::cursor_input_manager = CursorInputManager();
