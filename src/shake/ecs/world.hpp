#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>

#include "shake/core/type_traits/tagged_type.hpp"
#include "shake/core/std/map.hpp"
#include "shake/core/std/string.hpp"

#include "shake/ecs/component/component.hpp"
#include "shake/ecs/component/component_manager.hpp"
#include "shake/ecs/entity/entity.hpp"
#include "shake/ecs/entity/entity_manager.hpp"
#include "shake/ecs/system/system.hpp"
#include "shake/ecs/system/system_manager.hpp"

namespace shake {
namespace ecs {

class World
{
public:
    using Name = std::string;

public:

    //----------------------------------------------------------------
    World( const Name& name ) : m_name { name } { }

    //----------------------------------------------------------------
    // DEALING WITH ENTITIES

    inline EntityId create_entity()
    {
        return m_entity_manager.create_entity();
    }

    inline bool is_valid_entity( const EntityId entity_id )
    {
        return m_entity_manager.is_valid_entity( entity_id );
    }

    inline void destroy_entity( const EntityId entity_id )
    {
        m_entity_manager.destroy_entity( entity_id );
    }

    inline const EntityManager::EntityIdSet& get_entity_id_set() const
    {
        return m_entity_manager.get_entity_id_set();
    }

    //----------------------------------------------------------------
    // DEALING WITH COMPONENTS

    // The component will be copied!
    template<typename Component_T>
    inline void add_component_to_entity( const EntityId entity_id, const Component_T& component )
    {
        m_component_manager.add_component_to_entity( entity_id, component );
    }

    template<typename Component_T>
    inline bool entity_has_component( const EntityId entity_id ) const
    {
        return m_component_manager.entity_has_component<Component_T>( entity_id );
    }

    // non-const
    template<typename Component_T>
    inline Component_T& get_component_from_entity( const EntityId entity_id )
    {
        return m_component_manager.get_component_from_entity<Component_T>( entity_id );
    }

    // const
    template<typename Component_T>
    inline const Component_T& get_component_from_entity( const EntityId entity_id ) const
    {
        return m_component_manager.get_component_from_entity<Component_T>( entity_id );
    }

    template<typename Component_T>
    inline void destroy_component_from_entity( const EntityId entity_id )
    {
        m_component_manager.destroy_component_from_entity<Component_T>( entity_id );
    }

    //----------------------------------------------------------------
    // DEALING WITH SYSTEMS

    // The system will be copied!
    template<typename System_T>
    inline void add_system( const std::shared_ptr<System_T>& system )
    {
        m_system_manager.add_system( system );
    }

    void update_systems( float dt )
    {
        m_system_manager.update_all_systems( this, dt, m_entity_manager.get_entity_id_set() );
    }

private:
    Name                m_name;

    EntityManager       m_entity_manager;
    ComponentManager    m_component_manager;
    SystemManager       m_system_manager;
};

} // namespace ecs
} // namespace shake

#endif // WORLD_HPP
