#ifndef KEY_INPUT_MANAGER_HPP
#define KEY_INPUT_MANAGER_HPP

#include <string>
#include <map>
#include <vector>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Joystick.hpp>

enum class KeyInputSource
{
    KEYBOARD,
    GAMEPAD,
    MOUSE
};

struct KeyInputCode
{
    KeyInputSource source; // 入力種別
    int id;                // キーボードもパッドもマウスもintで指定できるためidとします
};

using KeyInputMapKeyType = std::string;

using KeyInputMap = std::map<KeyInputMapKeyType, std::vector<KeyInputCode>>;

class KeyInputManager
{
private:
    KeyInputMap input_map;                            // 入力とアクションの対応テーブル
    std::map<KeyInputMapKeyType, bool> current_input; // 現在の押下状態
    std::map<KeyInputMapKeyType, bool> last_input;    // 直前の押下状態

public:
    KeyInputManager();

    void add(KeyInputMapKeyType key, KeyInputSource source, int id);

    void delete_all();

    void update();

    bool is_pressed(KeyInputMapKeyType key) const;

    bool has_triggered(KeyInputMapKeyType key) const;

    bool has_released(KeyInputMapKeyType key) const;
};

#endif