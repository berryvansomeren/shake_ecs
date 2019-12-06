#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <cstdint>

#include "shake/core/macros/macro_strongly_typed_alias.hpp"

namespace shake {
namespace ecs {

//----------------------------------------------------------------
// Entities are nothing more than an Id
using EntityIdInternalType = uint64_t;
STRONGLY_TYPED_ALIAS( EntityId, EntityIdInternalType )

} // namespace ecs
} // namespace shake

#endif // ENTITY_HPP
