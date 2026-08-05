#include "Engine.h"

Engine::Engine(std::string window_name, unsigned int res_x, unsigned int res_y, bool VSync, bool fullscreen) : 
	controller(), renderer(controller, window_name, res_x, res_y, VSync, fullscreen)
{
	renderer.set_active_scene(world);
}

void Engine::refresh_scene()
{
	world.rebuild_queues();
}

/// @brief Updates the entire scene
/// @return float frame time in seconds
float Engine::update()
{
	float dt = timer.tick();
	return renderer.update().last() + world.update(dt);
}

float Engine::update(float dt)
{
	renderer.handle_events();
	return renderer.update().last() + world.update(dt);
}

void Engine::add_cube(bool phys_enabled, unsigned int side, size_t count)
{

	if (phys_enabled) for (int i = 0; i < count; i++) world.add_entity(RigidBody::Cube(side))->transform() = Transform({ pos(rng) }, { pos(rng) }, { pos(rng) });

	else for (int i = 0; i < count; i++) world.add_entity(Entity::Cube(side))->transform() = Transform({ pos(rng) }, { pos(rng) }, { pos(rng) });
}

void Engine::add_rectangle(bool phys_enabled, unsigned int width, unsigned int height, size_t count)
{

	if (phys_enabled) for (int i = 0; i < count; i++) world.add_entity(RigidBody::Rectangle(width, height))->transform() = Transform({pos(rng)}, {pos(rng)}, {pos(rng)});
	else for (int i = 0; i < count; i++) world.add_entity(Entity::Rectangle(width, height))->transform() = Transform({ pos(rng) }, { pos(rng) }, { pos(rng) });

	
}

void Engine::add_triangle(bool phys_enabled, unsigned int width, unsigned int height, size_t count)
{
	if (phys_enabled) for (int i = 0; i < count; i++) world.add_entity(RigidBody::Triangle(width, height))->transform() = Transform({ pos(rng) }, { pos(rng) }, { pos(rng) });
	else for (int i = 0; i < count; i++) world.add_entity(Entity::Triangle(width, height))->transform() = Transform({ pos(rng) }, { pos(rng) }, { pos(rng) });
}
