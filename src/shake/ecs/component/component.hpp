#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "shake/core/std/string.hpp"
#include "shake/core/math/transform_2d.hpp"
#include "shake/core/math/transform_3d.hpp"
#include "shake/core/macros/macro_strongly_typed_alias.hpp"
#include "shake/core/type_traits/type_id.hpp"

#include "shake/graphics/render_pack.hpp"

namespace shake {
namespace ecs {

//----------------------------------------------------------------
// Currently, the component base class is only used to erase types,
// so that we can have a map of different component storages.
// The TypeId is then used as key to access the right storage in the map.
// The component can then be cast to the correct sub-class.
class Component
{
public:
    STRONGLY_TYPED_ALIAS( TypeId, type_id::TypeId )

    Component() = default;

    virtual ~Component() = default;
};

//----------------------------------------------------------------
#define DEFINE_COMPONENT_WRAPPER( name, wrapped_type, wrapped_type_name ) \
    class name : public Component \
    { \
    public: \
        name( const wrapped_type& wrapped_type_name ) \
            : m_##wrapped_type_name { wrapped_type_name } \
        { } \
    \
    const wrapped_type& get_internal() const { return m_##wrapped_type_name; } \
          wrapped_type& get_internal()       { return m_##wrapped_type_name; } \
    \
    private: \
        wrapped_type m_##wrapped_type_name; \
    };

DEFINE_COMPONENT_WRAPPER( RenderComponent2D,    graphics::RenderPack2D, render_pack_2d  )
DEFINE_COMPONENT_WRAPPER( RenderComponent3D,    graphics::RenderPack3D, render_pack_3d  )
DEFINE_COMPONENT_WRAPPER( TransformComponent2D, Transform2D,            transform_2d    )
DEFINE_COMPONENT_WRAPPER( TransformComponent3D, Transform3D,            transform_3d    )

#undef DEFINE_COMPONENT_WRAPPER



} // namespace ecs
} // namespace shake

#endif // COMPONENT_HPP
