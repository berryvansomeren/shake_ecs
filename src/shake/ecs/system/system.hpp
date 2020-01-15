#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>

#include "shake/core/macros/macro_strongly_typed_alias.hpp"
#include "shake/core/type_traits/tagged_type.hpp"
#include "shake/core/type_traits/type_id.hpp"
#include "shake/core/std/set.hpp"
#include "shake/ecs/entity/entity.hpp"

namespace shake {
namespace ecs {

class World;

class System
{
public:
    STRONGLY_TYPED_ALIAS( TypeId, type_id::TypeId )

public:
    //----------------------------------------------------------------
    System() = default;

    //----------------------------------------------------------------
    virtual ~System() = default;
    virtual void update( float dt, World* world, const std::vector<EntityId>& entity_id_set ) = 0;

//    //----------------------------------------------------------------
//    inline void add_entity( const EntityId& entity_id )
//    {
//        shake::set::check_not_has( m_entity_id_set, entity_id );
//        m_entity_id_set.emplace( entity_id );
//    }

//    //----------------------------------------------------------------
//    inline bool has_entity( const EntityId& entity_id )
//    {
//        return shake::set::has( m_entity_id_set, entity_id );
//    }

//    //----------------------------------------------------------------
//    inline void remove_entity( const EntityId& entity_id )
//    {
//        shake::set::check_has( m_entity_id_set, entity_id );
//        m_entity_id_set.erase( entity_id );
//    }
};

} // namespace ecs
} // namespace shake

#endif // SYSTEM_HPP
