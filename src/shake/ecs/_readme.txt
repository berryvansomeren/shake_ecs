The ecs module provides the Entity Component Systems architecture
which makes managing game objects easier. 

The ECS architecture should not be aware of all existing component types. 
Instead a world keeps a map of component storages.
If an entity gets a component type that was not present in the world yet,
the world adds a new component storage to the map for the new type.
The component storages store a base class component,
which can be down_cast to the correct type through templated functions.

Named accessors that can be used from Python could be made later. 
They could simply be wrapped for every component type, so that the templated accessors are called internally.
However, at that point it might also make sense to remove the map of component storages,
and simply make a member storage for every component type explicitly.

The world now simply is an interface to the entity manager, component manager and systems manager.

(
The world could perhaps later be moved into scene.
A scene would then be the interface for entities, components and systems,
but also for updating transform hierarchies and spatial subdivision structures.
)
