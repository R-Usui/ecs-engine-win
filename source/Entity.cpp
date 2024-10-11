#include "Entity.hpp"

Entity::Entity(int unique_id, TagType tag)
    : unique_id{unique_id},
      tag{tag}
{
}

int Entity::get_unique_id() const
{
    return unique_id;
}

TagType Entity::get_tag() const
{
    return tag;
}

bool Entity::get_is_alive() const
{
    return is_alive;
}

void Entity::kill()
{
    is_alive = false;
}