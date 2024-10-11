#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <vector>
#include <memory>

#include "Scene.hpp"

class SceneManager
{
    using SceneMap = std::map<std::string, std::shared_ptr<Scene>>;
    SceneMap scenes;

    std::string current_key = "null";

public:
    SceneManager();

    template <typename T, typename... TArgs>
    void add(const std::string key, TArgs &&...args)
    {
        auto ptr = std::make_shared<T>(std::forward<TArgs>(args)...);
        scenes[key] = ptr;
    }

    void set(std::string key);

    std::string get_current_key();

    std::shared_ptr<Scene> get_current_scene();

    std::vector<std::string> get_all_keys();
};

#endif
