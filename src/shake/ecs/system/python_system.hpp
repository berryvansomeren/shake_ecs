#ifndef PYTHON_SYSTEM_HPP
#define PYTHON_SYSTEM_HPP

#include "shake/ecs/entity/entity.hpp"
#include "shake/ecs/system/system.hpp" 

namespace shake {
namespace ecs {

//----------------------------------------------------------------
// Class that enables Python classes to inherit from our C++ base class
class PythonSystem : public System
{
public:

    //----------------------------------------------------------------
    // Trampolines for virtual functions.
    // Necessary for Pybind

    // Inherit constructors
    using System::System;

    PythonSystem() : System() {}

    // This copy constructor is required to support copying PythonSystems
    // without losing the underlying corresponding Python context.
    // See also: https://github.com/pybind/pybind11/issues/1049
    PythonSystem( const System& system ) : System( system ) { }

    virtual void update( float dt, World* world, const std::vector<EntityId>& entity_id_set ) override;
};

} // namespace ecs
} // namespace shake

#endif // PYTHON_SYSTEM_HPP
