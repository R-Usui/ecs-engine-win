#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <map>

#include "Entity.hpp"

using EntityVector = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<TagType, EntityVector>;

class EntityManager
{
    EntityVector entities;
    EntityMap entity_map;
    size_t entity_count = 0;

public:
    EntityManager(){};

    // Must be called every frame
    void update();

    std::shared_ptr<Entity> add_entity(TagType tag);

    const EntityVector &get_entities();

    const EntityVector &get_entities(TagType tag);

    void delete_dead_entities(TagType tag);

    void delete_dead_entities();

    void delete_entities(TagType tag);

    void delete_entities();
};

#endif