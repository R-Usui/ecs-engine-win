#include "SceneManager.hpp"

SceneManager::SceneManager() {}

void SceneManager::set(std::string key)
{
    if (scenes.find(key) == scenes.end())
    {
        std::cout << "Failed to set key. (SceneManager does not have scene with key \"" << key << "\")" << std::endl;
    }
    else
    {
        current_key = key;
    }
}

std::string SceneManager::get_current_key()
{
    return current_key;
}

std::shared_ptr<Scene> SceneManager::get_current_scene()
{
    auto target = scenes.find(current_key);
    if (target == scenes.end())
    {
        std::cout << "Failed to return scene with unexisting key (" << current_key
                  << ") in SceneManager::get_current_scene(). nullptr was returned instead." << std::endl;

        return nullptr;
    }
    else
    {
        return target->second;
    }
}

std::vector<std::string> SceneManager::get_all_keys()
{
    std::vector<std::string> keys;

    for (const auto &[key, value] : scenes)
    {
        keys.push_back(key);
    }

    return keys;
}
