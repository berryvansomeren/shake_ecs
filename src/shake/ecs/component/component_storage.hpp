#ifndef COMPONENT_STORAGE_HPP
#define COMPONENT_STORAGE_HPP

#include <memory>

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/std/map.hpp"
#include "shake/core/macros/macro_debug_only.hpp"
#include "shake/core/type_traits/tagged_type.hpp"
#include "shake/core/type_traits/type_id.hpp"

#include "shake/ecs/entity/entity.hpp"
#include "shake/ecs/component/component.hpp"

namespace shake {
namespace ecs {

//----------------------------------------------------------------
// A component storage stores components of a single component type.
// Since it stores the cmponents as the component base type,
// it would theoretically be possible to mix different derived types that have been upcasted,
// however, some bookkeeping in the component_manager will prevent this.
// The component_manager will cast the based type to the correct derived type.
// The reason we store everything as the base type, is so that the component_manager
// can keep a simple map of non-templated component storages.
// TODO: Replace the reguler std::map with a custom handle map
class ComponentStorage
{
public:
    using ComponentMap  = std::map<EntityId, std::shared_ptr<Component>>;

public:
    //----------------------------------------------------------------
    // add a component to an entity
    template<typename Component_T>
    inline void add_component_to_entity( const EntityId id, const Component_T& component )
    {
        DEBUG_ONLY( CHECK( !map::has( m_components, id ), "Map has unexpected key" ) );
        m_components.emplace( id, std::make_shared<Component_T>( component ) ); // COPIES!!!
    }

    //----------------------------------------------------------------
    // query whether the entity has this component
    inline bool entity_has_component( const EntityId id ) const
    {
        return shake::map::has( m_components, id );
    }

    //----------------------------------------------------------------
    // get the component for a specific entity

    // non-const
    inline Component& get_component_from_entity( const EntityId id )
    {
        DEBUG_ONLY( CHECK( map::has( m_components, id ), "Map does not have expected key" ) );
        return *m_components.at( id );
    }

    // const
    inline const Component& get_component_from_entity( const EntityId id ) const
    {
        DEBUG_ONLY( CHECK( map::has( m_components, id ), "Map does not have expected key" ) );
        return *m_components.at( id );
    }

    //----------------------------------------------------------------
    // remove the component for a specific entity
    inline void destroy_component_from_entity( const EntityId id )
    {
        DEBUG_ONLY( CHECK( map::has( m_components, id ), "Map does not have expected key" ) );
        m_components.erase( id );
    }

private:
    ComponentMap m_components;
};

} // namespace ecs
} // namespace shake

#endif // COMPONENT_STORAGE_HPP
