#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include "shake/ecs/system/system.hpp"

namespace shake {
namespace ecs {

class RenderSystem
{
public:
    virtual void render( float dt, World* world, const std::vector<EntityId>& entity_id_set );
};

} // namespace ecs
} // namespace shake

#endif // RENDER_SYSTEM_HPP
