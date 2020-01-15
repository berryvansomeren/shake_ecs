#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include "shake/core/std/map.hpp"
#include "shake/core/type_traits/hierarchical_cast.hpp"
#include "shake/core/type_traits/type_id.hpp"

#include "shake/ecs/component/component_storage.hpp"

namespace shake {
namespace ecs {

//----------------------------------------------------------------
// The component manager keeps track of which components belong to which entities.
// It basically has a ComponentStorage for each component type.
class ComponentManager
{
public:
    using ComponentStorageMap = std::map< Component::TypeId, ComponentStorage >;

private:
    template<typename Component_T>
    inline void check_component_type_is_valid() const
    {
        static_assert( std::is_base_of<Component, Component_T>::value, "The provided component type is not derived from the Component class" );
    }

public:

    //----------------------------------------------------------------
    // DEALING WITH COMPONENT STORAGES

    //----------------------------------------------------------------
    // query whether a specific component storage exists

    template<typename Component_T>
    inline void add_component_storage()
    {
        check_component_type_is_valid<Component_T>();
        const auto component_type_id = Component::TypeId { type_id::get<Component_T>() };
        m_component_storages.emplace( component_type_id, ComponentStorage { } );
    }

    //----------------------------------------------------------------
    // query whether a specific component storage exists
    template<typename Component_T>
    inline bool has_component_storage() const
    {
        check_component_type_is_valid<Component_T>();
        const auto component_type_id = Component::TypeId { type_id::get<Component_T>() };
        return map::has( m_component_storages, component_type_id );
    }

    //----------------------------------------------------------------
    // get a specific component storage

    // non-const
    template<typename Component_T>
    inline ComponentStorage& get_component_storage()
    {
        check_component_type_is_valid<Component_T>();
        DEBUG_ONLY( CHECK( has_component_storage<Component_T>(), "Map does not have expected key" ) );
        const auto component_type_id = Component::TypeId { type_id::get<Component_T>() };
        return m_component_storages.at( component_type_id );
    }

    // const
    template<typename Component_T>
    inline const ComponentStorage& get_component_storage() const
    {
        check_component_type_is_valid<Component_T>();
        DEBUG_ONLY( CHECK( has_component_storage<Component_T>(), "Map does not have expected key" ) );
        const auto component_type_id = Component::TypeId { type_id::get<Component_T>() };
        return m_component_storages.at( component_type_id );
    }

    template<typename Component_T>
    inline ComponentStorage& get_or_add_component_storage()
    {
        check_component_type_is_valid<Component_T>();
        if ( !has_component_storage<Component_T>() )
        {
            add_component_storage<Component_T>();
        }
        return get_component_storage<Component_T>();
    }

    //----------------------------------------------------------------
    // DEALING WITH ENTITIES AND THEIR COMPONENTS

    //----------------------------------------------------------------
    // Add a specific component to an entity
    template<typename Component_T>
    inline void add_component_to_entity( const EntityId entity_id, const Component_T& component )
    {
        check_component_type_is_valid<Component_T>();
        auto& component_storage = get_or_add_component_storage<Component_T>();
        component_storage.add_component_to_entity( entity_id, component );
    }

    //----------------------------------------------------------------
    // Check if the entity has a specific component.
    template<typename Component_T>
    inline bool entity_has_component( const EntityId entity_id ) const
    {
        check_component_type_is_valid<Component_T>();
        if ( !has_component_storage<Component_T>() )
        {
            return false;
        }
        else
        {
            auto& component_storage = get_component_storage<Component_T>();
            return component_storage.entity_has_component( entity_id );
        }
    }

    //----------------------------------------------------------------
    // Get a specific component for an entity.

    // non-const
    template<typename Component_T>
    inline Component_T& get_component_from_entity( const EntityId entity_id )
    {
        check_component_type_is_valid<Component_T>();
        DEBUG_ONLY( CHECK( has_component_storage<Component_T>(), "There is no component storage for the requested component type" ) );
        auto& component_storage = get_component_storage<Component_T>();
        auto& component = component_storage.get_component_from_entity( entity_id );
        return unsafe_down_cast<Component_T>( component );
    }

    // const
    template<typename Component_T>
    inline const Component_T& get_component_from_entity( const EntityId entity_id ) const
    {
        check_component_type_is_valid<Component_T>();
        DEBUG_ONLY( CHECK( has_component_storage<Component_T>(), "There is no component storage for the requested component type" ) );
        auto& component_storage = get_component_storage<Component_T>();
        auto& component = component_storage.get_component_from_entity( entity_id );
        return unsafe_down_cast<const Component_T>( component );
    }

    //----------------------------------------------------------------
    // Remove a specific component for an entity.
    template<typename Component_T>
    inline void destroy_component_from_entity( const EntityId entity_id )
    {
        check_component_type_is_valid<Component_T>();
        DEBUG_ONLY( CHECK( has_component_storage<Component_T>(), "There is no component storage for the requested component type" ) );
        auto& component_storage = get_component_storage<Component_T>();
        component_storage.destroy_component_from_entity( entity_id );
    }

private:
    ComponentStorageMap m_component_storages;
};

} // namespace ecs
} // namespace shake

#endif // COMPONENT_MANAGER_HPP
