#include "Scene.h"

Scene::~Scene()
{
	spdlog::set_pattern("[%M:%S.%e] %v");
	
	
	std::cout << "=============SCENE SHUTDOWN=============\n\n";
	for (auto& i : entities) {  //For each entity in the scene
		spdlog::info("{}{}{} was destroyed",
			"\x1b[1;33m", i->name(), "\x1b[0m");
		delete i;               //Delete it
	}
	std::cout << "\n========================================\n";
}

Entity* Scene::add_entity(Entity* e)
{
	e->_id = next_id++;
	e->_name += ("_" + std::to_string(e->_id));

	entities.push_back(e);
	//if (e->is_visibile() == true) visible.push_back(e);

	//rebuild_queues();

	return entities.back();
}

void Scene::reserve(size_t entities_count)
{
	entities.reserve(entities_count);
	
	visible.reserve(entities_count);
	physics.reserve(entities_count);
}

void Scene::reserve_queues(size_t entities_count){
	visible.reserve(entities_count);
	physics.reserve(entities_count);
}

void Scene::add_entity(const std::vector<Entity*>& to_add)
{

	for (auto *i : to_add) {
		add_entity(i);
	}
}

void Scene::delete_entity(Entity*& e)    //Treat e as key, not as target. Scene's vector is the source of truth!
{
	auto it = std::find(entities.begin(), entities.end(), e);

	if (it != entities.end()) { //If we found the entity in the the scene
		delete* it;             //We invalidate it 
		entities.erase(it);     //And remove it
	}

	it = std::find(visible.begin(), visible.end(), e);
	if (it != visible.end()) { //If we found the entity in the the scene
		delete* it;             //We invalidate it 
		visible.erase(it);     //And remove it
	}


	e = nullptr;

}

void Scene::delete_entity(const std::vector<Entity*>& e)   //Treat e as key, not as target. Scene's vector is the source of truth!
{

   
	for (auto* ptr : e) {   //For each element we want to remove

		delete_entity(ptr); //Call the function that does it
		
	}

}

void Scene::delete_last_entity()
{
	if (!entities.empty()) {
		delete entities.back();
		entities.pop_back();
	}
}

void Scene::rebuild_visible()
{
	visible.clear();

	for(auto entity : entities){
		if (entity->is_visibile() == true) {
			visible.push_back(entity);
		}
	}

}

void Scene::rebuild_physics()
{
	physics.clear();

	for (auto entity : entities) {

		RigidBody* rb = dynamic_cast<RigidBody*>(entity);
		if (rb != nullptr && rb->is_simulated()) {
			physics.push_back((RigidBody*)entity);

		}
	}

	simulator.set_active_scene(physics);
}

float Scene::update(float dt)
{

	(simulator).update(dt);
	
	return timer.tick();
}

void Scene::rebuild_queues()
{
	rebuild_physics();
	rebuild_visible();
}
