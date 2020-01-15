#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/std/set.hpp"
#include "shake/core/macros/macro_debug_only.hpp"
#include "shake/core/macros/macro_property.hpp"

#include "entity.hpp"

namespace shake {
namespace ecs {

class EntityManager
{
public:
    using EntityIdSet = std::set<EntityId>;

public:
    EntityManager() = default;

    //----------------------------------------------------------------
    inline EntityId create_entity()
    {
        auto new_entity_id = m_next_entity_id;
        (*m_next_entity_id)++;
        m_entity_id_set.emplace( new_entity_id );
        return new_entity_id;
    }

    //----------------------------------------------------------------
    inline bool is_valid_entity( const EntityId entity_id )
    {
        return shake::set::has( m_entity_id_set, entity_id );
    }

    //----------------------------------------------------------------
    inline void destroy_entity( const EntityId entity_id )
    {
        DEBUG_ONLY( CHECK( is_valid_entity( entity_id ), "Map does not have expected key" ) );
        m_entity_id_set.erase( entity_id );
    }

    //----------------------------------------------------------------
    inline void destroy_all_entities()
    {
        m_entity_id_set.clear();
        m_next_entity_id = EntityId { 0 };
    }

private:
    EntityId                    m_next_entity_id    { 0 };

    PROPERTY_R( EntityIdSet,    entity_id_set )
};

} // namespace ecs
} // namespace shake

#endif // ENTITY_MANAGER_HPP
