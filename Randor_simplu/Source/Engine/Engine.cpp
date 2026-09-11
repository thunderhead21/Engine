#include "Engine.h"

void Engine::on_create() {
	std::cout << "ENGINE on_create()" << std::endl;
}
Engine::Engine(std::string window_name, unsigned int res_x, unsigned int res_y, bool VSync, bool fullscreen) : 
	controller(), renderer(controller, window_name, res_x, res_y, VSync, fullscreen)
{
	on_create();
	renderer.set_active_scene(world);
}

void Engine::on_destroy()
{
	std::cout << "Engine instance destroyed" << std::endl;
}
Engine::~Engine()
{
	on_destroy();
}







void Engine::refresh_scene()
{
	world.rebuild_queues();
}

void Engine::on_update() {
	static unsigned short count = 0;
	if (count < 5) {
		std::cout << "ENGINE on_update()" << std::endl;
		count++;
	}
}
/// @brief Updates the entire scene.
/// @return float frame time in seconds
float Engine::update(float dt)
{
	if (renderer.get_validity() == 0){
		valid = 0;
		quit();
		return 0;
	}
	if (dt < 0) dt = timer.tick();

	renderer.handle_events();

	on_update();

	return renderer.update().last() + world.update(dt);
}


bool Engine::running()
{
	return renderer.get_validity();
}

void Engine::on_quit() {
	std::cout << "ENGINE on_quit()" << std::endl;

}

void Engine::quit()
{
	renderer.quit();
	on_quit();
}

void Engine::add_cube(bool phys_enabled, unsigned int side, size_t count)
{

	if (phys_enabled) for (int i = 0; i < count; i++) world.add_entity(RigidBody::Cube(side))->transform() = Transform({ pos(rng), pos(rng), pos(rng) + 2300}, { pos(rng), pos(rng), pos(rng)}, { pos(rng) });

	else for (int i = 0; i < count; i++) world.add_entity(Entity::Cube(side))->transform() = Transform({ pos(rng),pos(rng), pos(rng)}, { pos(rng), pos(rng), pos(rng)}, { pos(rng) });
}

void Engine::add_rectangle(bool phys_enabled, unsigned int width, unsigned int height, size_t count)
{

	if (phys_enabled) for (int i = 0; i < count; i++) world.add_entity(RigidBody::Rectangle(width, height))->transform() = Transform({pos(rng),pos(rng) ,pos(rng) + 2300 }, {pos(rng),pos(rng),pos(rng) }, {pos(rng)});
	else for (int i = 0; i < count; i++) world.add_entity(Entity::Rectangle(width, height))->transform() = Transform({ pos(rng),pos(rng),pos(rng) }, { pos(rng),pos(rng),pos(rng) }, { pos(rng) });

	
}

void Engine::add_triangle(bool phys_enabled, unsigned int width, unsigned int height, size_t count)
{
	if (phys_enabled) for (int i = 0; i < count; i++) world.add_entity(RigidBody::Triangle(width, height))->transform() = Transform({ pos(rng), pos(rng), pos(rng), }, { pos(rng),pos(rng), pos(rng)}, { pos(rng) });
	else for (int i = 0; i < count; i++) world.add_entity(Entity::Triangle(width, height))->transform() = Transform({ pos(rng), pos(rng), pos(rng)}, { pos(rng), pos(rng), pos(rng)}, { pos(rng) });
}
