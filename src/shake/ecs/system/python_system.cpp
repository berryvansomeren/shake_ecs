#include "python_system.hpp"

#include <pybind11/embed.h>

#include "shake/ecs/world.hpp"

namespace shake {
namespace ecs {

//----------------------------------------------------------------
void PythonSystem::update( float dt, World* world, const std::vector<EntityId>& entity_id_set )
{
    PYBIND11_OVERLOAD_PURE // remove "PURE" if the function doesn have a default implementation
    (
        void,           // return type
        System,         // base class
        update,         // name of function in c++
        dt,             // param
        world,          // param
        entity_id_set   // param
    );
}

} // namespace ecs
} // namespace shake
