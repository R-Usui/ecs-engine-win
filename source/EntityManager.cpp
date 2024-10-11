#include <algorithm>

#include "EntityManager.hpp"

void EntityManager::delete_dead_entities(TagType tag)
{
    auto is_target = [=](std::shared_ptr<Entity> e) -> bool
    {
        // is_dead == trueかつ指定されたTagであること
        return !e->get_is_alive() && e->get_tag() == tag;
    };

    // EntityManager::entitiesから削除
    std::erase_if(entities, is_target);

    // EntitiesManager::entity_mapから削除
    for (auto &[_, entities] : entity_map)
    {
        std::erase_if(entities, is_target);
    }
}

void EntityManager::delete_dead_entities()
{
    auto is_target = [=](std::shared_ptr<Entity> e) -> bool
    {
        // is_dead == trueであること
        return !e->get_is_alive();
    };

    // EntityManager::entitiesから削除
    std::erase_if(entities, is_target);

    // EntitiesManager::entity_mapから削除
    for (auto &[_, entities] : entity_map)
    {
        std::erase_if(entities, is_target);
    }
}

void EntityManager::delete_entities(TagType tag)
{
    auto is_target = [=](std::shared_ptr<Entity> e) -> bool
    {
        // 指定されたTagであること
        return e->get_tag() == tag;
    };

    // EntityManager::entitiesから削除
    std::erase_if(entities, is_target);

    // EntitiesManager::entity_mapから削除
    for (auto &[_, entities] : entity_map)
    {
        std::erase_if(entities, is_target);
    }
}

void EntityManager::delete_entities()
{

    auto is_target = [](std::shared_ptr<Entity> e) -> bool
    {
        return true;
    };

    // EntityManager::entitiesから削除
    std::erase_if(entities, is_target);

    // EntitiesManager::entity_mapから削除
    for (auto &[_, entities] : entity_map)
    {
        std::erase_if(entities, is_target);
    }
}

void EntityManager::update()
{
    delete_dead_entities();
}

std::shared_ptr<Entity> EntityManager::add_entity(TagType tag)
{
    // 1. create a new entity object
    auto e = std::shared_ptr<Entity>(new Entity(entity_count, tag));
    ++entity_count;

    // 2. store it to the entities and entitiy_map
    entities.push_back(e);
    entity_map[tag].push_back(e);

    // 3. return the shared pointer pointing to that entity
    return e;
}

const EntityVector &EntityManager::get_entities()
{
    return entities;
}

const EntityVector &EntityManager::get_entities(TagType tag)
{
    return entity_map[tag];
}
