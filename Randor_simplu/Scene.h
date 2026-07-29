#pragma once

#include "Entity.h"
#include "Physics.h"
/// @brief Scene object. Affected by physics an input.

class Scene
{
protected:
	Physics simulator;
	Timer timer;

	std::vector<Entity*> entities;		//ALL entities
	
	std::vector<Entity*> visible;		//Visible ones for rendering
	std::vector<RigidBody*> physics;	//Physically simulated entities
	
	size_t next_id;

	void rebuild_visible();
	void rebuild_physics();


public:
	Scene():next_id(1) {};
	~Scene();

	Entity* add_entity(Entity* e);

	/// @brief Adds the provided entities to the scene
	/// @param to_add std::vector of Entity pointers. Updated with the addresses in the scene.
	/// @return 
	void add_entity(const std::vector<Entity*>& to_add);
 
	void delete_entity(Entity*& e);
	void delete_entity(const std::vector<Entity*>& e);
	
	void delete_last_entity();

	const std::vector<Entity*>& get_entities() const noexcept{ return entities; };
	const std::vector<Entity*>& get_visible_entities() const noexcept { return visible; };
	

	//Iterators
	std::vector<Entity*>::const_iterator begin() const noexcept { return entities.begin(); };
	std::vector<Entity*>::iterator begin()  noexcept { return entities.begin(); };

	std::vector<Entity*>::const_iterator end() const noexcept{ return entities.end(); };
	std::vector<Entity*>::iterator end() noexcept { return entities.end(); };

	//State inspectors
	size_t size() const noexcept { return entities.size(); };
	bool  empty() const noexcept { return entities.empty();};


	float update(float dt);

	void rebuild_queues();
};

