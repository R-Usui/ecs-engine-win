#include <iostream>

#include "KeyInputManager.hpp"

KeyInputManager::KeyInputManager()
{
}

void KeyInputManager::add(KeyInputMapKeyType action, KeyInputSource source, int id)
{
    input_map[action].push_back(KeyInputCode{source, id});
}

void KeyInputManager::delete_all()
{
    std::cout << "ButtonInput::delete_all() called" << std::endl;

    input_map.clear();
}

/// 入力情報を更新する(毎フレーム呼び出してください)
void KeyInputManager::update()
{
    sf::Joystick::update();

    last_input = current_input;

    // それぞれのアクション名に割り当たっている全ての入力をチェック
    for (const auto &[key, values] : input_map)
    {
        bool is_pressed = false;

        for (const auto &value : values)
        {
            if (value.source == KeyInputSource::KEYBOARD)
            {
                auto key = static_cast<sf::Keyboard::Key>(value.id);
                is_pressed = sf::Keyboard::isKeyPressed(key);
            }
            else if (value.source == KeyInputSource::MOUSE)
            {
                auto button = static_cast<sf::Mouse::Button>(value.id);
                is_pressed = sf::Mouse::isButtonPressed(button);
            }
            else if (value.source == KeyInputSource::GAMEPAD)
            {
                is_pressed = sf::Joystick::isButtonPressed(0, value.id);
            }

            if (is_pressed)
            { // ヒットしたらループを抜ける
                break;
            }
        }

        current_input[key] = is_pressed;
    }
}

/// 入力チェック(押下状態)
bool KeyInputManager::is_pressed(const KeyInputMapKeyType action) const
{
    if (current_input.find(action) == current_input.end())
    {
        // 未定義のボタン名が来たら無条件でfalseを返す(若しくはassert起こす)
        return false;
    }
    else
    {
        return current_input.at(action);
    }
}

/// 入力チェック(トリガー状態[押した瞬間])
bool KeyInputManager::has_triggered(const KeyInputMapKeyType action) const
{
    if (current_input.find(action) == current_input.end() ||
        last_input.find(action) == last_input.end())
    {
        // 未定義のボタン名が来たら無条件でfalseを返す
        return false;
    }

    return current_input.at(action) && !last_input.at(action);
}

/// 入力チェック(トリガー状態（離した瞬間])
bool KeyInputManager::has_released(const KeyInputMapKeyType action) const
{
    if (current_input.find(action) == current_input.end() ||
        last_input.find(action) == last_input.end())
    {
        // 未定義のボタン名が来たら無条件でfalseを返す
        return false;
    }

    return !current_input.at(action) && last_input.at(action);
}