#include <string>

#include "Scene.hpp"
#include "Grobal.hpp"

class Engine
{
private:
    sf::RenderWindow window;

    void _init_window();

    void _init_scene_manager();

    void start_scene();

    void end_scene();

public:
    Engine();

    void run();
};