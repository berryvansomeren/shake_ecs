#include "render_system.hpp"

#include "shake/core/log.hpp"

#include "shake/ecs/entity/entity_filter.hpp"
#include "shake/ecs/world.hpp"

#include "shake/graphics/draw.hpp"

namespace shake {
namespace ecs {

namespace { // anonymous

//----------------------------------------------------------------
void update_2d( float dt, World* world, const std::vector<EntityId>& entity_id_set )
{
    // c++17
    //const auto entity_ids = get_filtered_entity_ids<RenderComponent2D, TransformComponent2D>( world, entity_id_set );
    
    /*for ( const auto& entity_id : entity_id_set )
    {
        if (!world->entity_has_component<RenderComponent2D>( entity_id ) )      { continue; }
        if (!world->entity_has_component<TransformComponent2D>( entity_id ) )   { continue; }
        
        auto& render_pack   = world->get_component_from_entity<RenderComponent2D>   ( entity_id ).get_internal();
        auto& transform     = world->get_component_from_entity<TransformComponent2D>( entity_id ).get_internal();
        graphics::draw( render_pack, transform );
    }*/
}

//----------------------------------------------------------------
void update_3d( float dt, World* world, const std::vector<EntityId>& entity_id_set )
{
    // c++17
    //const auto entity_ids = get_filtered_entity_ids<RenderComponent3D, TransformComponent3D>( world, entity_id_set );

    for ( const auto& entity_id : entity_id_set )
    {
        if (!world->entity_has_component<RenderComponent3D>( entity_id ) )      
        {   
            LOG( "Doesnt have RenderComponent" );
            continue; 
        }
        if (!world->entity_has_component<TransformComponent3D>( entity_id ) )   
        { 
            LOG( "Doesnt have TransformComponent" );
            continue; 
        }

        auto& render_pack   = world->get_component_from_entity<RenderComponent3D>   ( entity_id ).get_internal();
        auto& transform     = world->get_component_from_entity<TransformComponent3D>( entity_id ).get_internal();
        graphics::draw( render_pack, transform );
    }
}

} // namespace anonymous

//----------------------------------------------------------------
void RenderSystem::render( float dt, World* world, const std::vector<EntityId>& entity_id_set )
{
    update_2d( dt, world, entity_id_set );
    update_3d( dt, world, entity_id_set );
}

} // namespace ecs
} // namespace shake
