#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>
#include <array>
#include <memory>
#include <bitset>

#include "Component.hpp"

inline int get_new_component_type_ID()
{
    static int result = 0;
    return result++;
}

template <typename T>
inline int get_component_type_ID() noexcept
{
    static int result = get_new_component_type_ID();
    return result;
}

constexpr int MAX_COMPONENTS = 32;

using ComponentBitset = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<std::shared_ptr<Component>, MAX_COMPONENTS>;

using TagType = std::string;

class EntityManager;

class Entity
{
    friend class EntityManager;

    int unique_id;
    TagType tag;

    bool is_alive = true;

    ComponentArray component_array;
    ComponentBitset component_bitset;

    Entity(int unique_id, TagType tag = "");

public:
    int get_unique_id() const;
    TagType get_tag() const;

    bool get_is_alive() const;
    void kill();

    template <typename T>
    bool has_component() const
    {
        auto type_id = get_component_type_ID<T>();
        return component_bitset[type_id];
    }

    template <typename T, typename... TArgs>
    std::shared_ptr<T> add_component(TArgs &&...args)
    {
        auto ptr = std::make_shared<T>(std::forward<TArgs>(args)...);
        component_array[get_component_type_ID<T>()] = ptr;
        component_bitset[get_component_type_ID<T>()] = true;
        return ptr;
    }

    template <typename T>
    std::shared_ptr<T> get_component() const
    {
        std::shared_ptr<Component> ptr = component_array[get_component_type_ID<T>()];
        return std::static_pointer_cast<T>(ptr);
    }

    template <typename T>
    void delete_component()
    {
        component_array[get_component_type_ID<T>()] = nullptr;
        component_bitset[get_component_type_ID<T>()] = false;
    }
};

#endif