#ifndef ENTITY_FILTER_HPP
#define ENTITY_FILTER_HPP

#include <vector>

#include "shake/core/std/set.hpp"

#include "shake/ecs/entity/entity.hpp"
#include "shake/ecs/world.hpp"

namespace shake {
namespace ecs {

//----------------------------------------------------------------
template<typename... Component_Ts>
std::vector<EntityId> get_filtered_entity_ids( World* world, const std::vector<EntityId>& entity_ids )
{
    auto result = std::vector<EntityId> { };
    for ( const auto& entity_id : entity_ids )
    {
        if ( ( world->entity_has_component<Component_Ts>( entity_id ) && ... ) )
        {
            result.emplace_back( entity_id );
        }
    }
    return result;
}

} // namespace ecs
} // namespace shake

#endif // ENTITY_FILTER_HPP
