#ifndef SYSTEM_MANAGER_HPP
#define SYSTEM_MANAGER_HPP

#include <memory>

#include <pybind11/pybind11.h>

#include "shake/core/contracts/contracts.hpp"
#include "shake/core/std/map.hpp"
#include "shake/core/macros/macro_debug_only.hpp"

#include "shake/ecs/system/system.hpp"
#include "shake/ecs/system/python_system.hpp"

namespace shake {
namespace ecs {

class World;

class SystemManager
{
private:
    // this is a shared ptr for easier integration with pybind11
    using SystemMap = std::map<System::TypeId, std::shared_ptr<System>>;

    using PythonSystemStorage = std::vector<std::shared_ptr<System>>;

private:
    template<typename System_T>
    inline void check_system_type_is_valid() const
    {
        static_assert( std::is_base_of<System, System_T>::value, "The provided system type is not derived from the System class" );
    }

public:

    //----------------------------------------------------------------
    // copies the system to the system map
    template<typename System_T>
    inline void add_system( const std::shared_ptr<System_T>& system )
    {
        check_system_type_is_valid<System_T>();
        const auto system_type_id = System::TypeId{ type_id::get<System_T>() };
        m_systems.emplace( system_type_id, system ); // COPIES!!!
    }

    //----------------------------------------------------------------
    // copies the system to the system map
    inline void add_python_system( const std::shared_ptr<System>& system )
    {
        // Okay this is complex.
        // If we would simply copy the shared pointer to the map,
        // the related python object will be lost,
        // and the System which actually has an underlying python implementation,
        // will decay into a System without python implementation,
        // resulting in pure virtual functions being called.
        // We therefore need to do a complex copy.
        // This process relies on the python implementation defining a clone function!
        // Also see: https://github.com/pybind/pybind11/issues/1049
        auto python_system = pybind11::cast( system );
        auto cloned_python_system = python_system.attr( "clone" )();
        auto keep_python_state_alive = std::make_shared<pybind11::object>( cloned_python_system );
        auto ptr = cloned_python_system.cast<PythonSystem*>();

        // This uses the aliasing shared ptr constructor,
        // which makes a distinciton between the object that it owns / refers to
        // and the object / data that it actually stores
        //m_systems.emplace_back( keep_python_state_alive, ptr );
    }

    //----------------------------------------------------------------
    template<typename System_T>
    inline bool has_system()
    {
        check_system_type_is_valid<System_T>();
        const auto system_type_id = System::TypeId{ type_id::get<System_T>() };
        return map::has( m_systems, system_type_id );
    }

    //----------------------------------------------------------------
    inline void update_all_systems( World* world, float dt, const std::set<EntityId>& entity_id_set )
    {
        auto vec = std::vector<EntityId>{ };
        for ( const auto& entity_id : entity_id_set )
        {
            vec.emplace_back( entity_id );
        }

        for ( auto& system : m_systems )
        {
            system.second->update( dt, world, vec );
        }
    }

private:
    SystemMap m_systems;
};

} // namespace ecs
} // namespace shake

#endif // SYSTEM_MANAGER_HPP
