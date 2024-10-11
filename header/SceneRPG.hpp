#ifndef SCENE_RPG_HPP
#define SCENE_RPG_HPP

#include <string>
#include <map>

#include "Scene.hpp"
#include "Grobal.hpp"

namespace RPG
{
    class Element
    {
    public:
        enum class Type : int
        {
            NORMAL = 0,
            FIRE,
            WATER,
            LEAF,
            LIGHT,
            SHADOW,
        } type;

        Element(Type type)
            : type{type}
        {
        }

        Element(const Element &other)
        {
            this->type = other.type;
        }

        bool is_stronger_than(const Element &other)
        {
            return (this->type == Type::FIRE && other.type == Type::LEAF) ||
                   (this->type == Type::WATER && other.type == Type::FIRE) ||
                   (this->type == Type::LEAF && other.type == Type::WATER) ||
                   (this->type == Type::LIGHT && other.type == Type::SHADOW) ||
                   (this->type == Type::SHADOW && other.type == Type::LIGHT);
        }

        std::string get_name()
        {
            switch (type)
            {
            case Type::NORMAL:
                return "NORMAL";
            case Type::FIRE:
                return "FIRE";
            case Type::WATER:
                return "WATER";
            case Type::LEAF:
                return "LEAF";
            case Type::LIGHT:
                return "LIGHT";
            case Type::SHADOW:
                return "SHADOW";
            }
        }
    };

    class Art
    {
    public:
        enum class Type : int
        {
            PHISYCAL = 0,
            MAGIC,
            SHIELD,
            BARRIER,
            HEALING,
        } type;

        Art(Type type)
            : type{type}
        {
        }

        Art(const Art &other)
        {
            this->type = other.type;
        }
    };

    class Skill
    {
    public:
        std::string name;
        int power;
        int mp;
        Art::Type art;
        Element::Type element;

        Skill(std::string name, int power, int mp, Art::Type art, Element::Type element = Element::Type::NORMAL)
            : name{name}, power{power}, mp{mp}, art{art}, element{element}
        {
        }

        Skill()
            : Skill("Default", 500, 100, Art::Type::PHISYCAL)
        {
        }
    };

    std::map<std::string, Skill> skill_DB;

    class Monster
    {
    public:
        std::string name;

        int max_hp;
        int max_mp;

        std::map<Art::Type, int> parameter = {{Art::Type::PHISYCAL, 100},
                                              {Art::Type::MAGIC, 100},
                                              {Art::Type::SHIELD, 50},
                                              {Art::Type::BARRIER, 50},
                                              {Art::Type::HEALING, 30}};

        int current_hp;
        int current_mp;

        std::vector<std::string> skill_keys;

        void add_skill(const std::string &key)
        {
            skill_keys.push_back(key);
        }

        Monster(std::string name, int max_hp, int max_mp)
            : name{name}, max_hp{max_hp}, max_mp{max_mp}
        {
        }

        Monster()
            : Monster("Default", 500, 100)
        {
        }
    };

    std::map<std::string, Monster> monster_DB;
}

class SceneRPG : public Scene
{
private:
    void _init_skill_DB()
    {
        using namespace RPG;

        skill_DB["Kick"] = Skill("Kick", 100, 0, Art::Type::PHISYCAL);
        skill_DB["Fire"] = Skill("Fire", 100, 0, Art::Type::MAGIC, Element::Type::FIRE);
        skill_DB["Guard"] = Skill("Guard", 100, 0, Art::Type::SHIELD);
        skill_DB["Barrier"] = Skill("Barrier", 100, 0, Art::Type::BARRIER);
        skill_DB["Rest"] = Skill("Rest", 100, 1, Art::Type::HEALING);
    }

    void _init_monster_DB()
    {
        using namespace RPG;

        std::string name = "Slime";
        monster_DB[name] = Monster(name, 500, 100);
        monster_DB[name].parameter[Art::Type::PHISYCAL] = 120;
        monster_DB[name].add_skill("Kick");

        name = "Witch";
        monster_DB[name] = Monster(name, 480, 120);
        monster_DB[name].parameter[Art::Type::MAGIC] = 120;
        monster_DB[name].add_skill("Fire");
    }

    void
    _spawn_help_label()
    {
        auto e = entity_manager.add_entity("label");

        e->add_component<CTransform>(Vec2(0, 0));
        e->get_component<CTransform>()->will_ignore_camera_position = true;

        e->add_component<CText>("SceneRPG.hpp (Press Shift+M to return home scene)", "mario", 18);
    }

    void sys_change_scene()
    {
        if ((Grobal::button_input_manager.is_pressed("lshift") || Grobal::button_input_manager.is_pressed("rshift")) &&
            Grobal::button_input_manager.has_triggered("M"))
        {
            should_end = true;
            next_scene_key = "main";
        }
    }

    void sys_debug()
    {
        using namespace RPG;
        Element element01 = Element(Element::Type::FIRE);
        Element element02 = Element(Element::Type::LEAF);
        std::cout << element01.get_name() << " is stronger than " << element02.get_name() << "? = " << element01.is_stronger_than(element02) << std::endl;
    }

public:
    SceneRPG()
    {
    }

    void call_sub_systems() override
    {
        sys_change_scene();
    }

    void register_asset() override
    {
        std::cout << "SceneRPG::register_asset() called" << std::endl;

        Grobal::font_manager.add("mario", "mario.ttf");
    }

    void register_input() override
    {
        std::cout << "SceneRPG::register_input() called" << std::endl;

        Grobal::button_input_manager.add("LCLICK", KeyInputSource::MOUSE, sf::Mouse::Left);

        Grobal::button_input_manager.add("ENTER", KeyInputSource::KEYBOARD, sf::Keyboard::Enter);
        Grobal::button_input_manager.add("SPACE", KeyInputSource::KEYBOARD, sf::Keyboard::Space);
        Grobal::button_input_manager.add("BS", KeyInputSource::KEYBOARD, sf::Keyboard::BackSpace);
        Grobal::button_input_manager.add("ESCAPE", KeyInputSource::KEYBOARD, sf::Keyboard::Escape);

        Grobal::button_input_manager.add("UP", KeyInputSource::KEYBOARD, sf::Keyboard::Up);
        Grobal::button_input_manager.add("DOWN", KeyInputSource::KEYBOARD, sf::Keyboard::Down);
        Grobal::button_input_manager.add("LEFT", KeyInputSource::KEYBOARD, sf::Keyboard::Left);
        Grobal::button_input_manager.add("RIGHT", KeyInputSource::KEYBOARD, sf::Keyboard::Right);

        Grobal::button_input_manager.add("M", KeyInputSource::KEYBOARD, sf::Keyboard::M);
        Grobal::button_input_manager.add("lshift", KeyInputSource::KEYBOARD, sf::Keyboard::LShift);
        Grobal::button_input_manager.add("rshift", KeyInputSource::KEYBOARD, sf::Keyboard::RShift);
    }

    void when_start() override
    {
        std::cout << "SceneRPG::when_start() called" << std::endl;

        _spawn_help_label();

        sys_debug();

        count = 0;
    }

    void when_end() override
    {
        std::cout << "SceneRPG::when_end() called" << std::endl;

        entity_manager.delete_entities();
    }
};

#endif