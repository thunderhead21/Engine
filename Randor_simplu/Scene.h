#pragma once

#include <string>

#include "Entity.h"
#include "Physics.h"

/// @brief Scene object. Affected by physics and input.
/// @brief Owns a physics solver which affects the physics-enabled objects
class Scene
{
protected:
	Physics simulator;
	Timer timer;	//Used to compute simulation times, not dt

	std::vector<Entity*> entities;		//ALL entities
	
	std::vector<Entity*> visible;		//Visible ones for rendering
	std::vector<RigidBody*> physics;	//Physically simulated entities
	
	//Used to compute the next entity's ID
	//0 is reserved for invalid entities that should be ignored!
	size_t next_id;		

	/// @brief Rebuilds the Scene's entity queue
	void rebuild_visible();
	/// @brief Rebuilds the Scene's entity queue
	void rebuild_physics();


public:
	Scene():next_id(1) {};
	~Scene();

	//Appends an entity to the scene by pointer
	Entity* add_entity(Entity* e);

	/// @brief Adds the provided entities to the scene
	/// @param to_add std::vector of Entity pointers. Updated with the addresses in the vector.
	void add_entity(const std::vector<Entity*>& to_add);
 
	void delete_entity(Entity*& e);
	void delete_entity(const std::vector<Entity*>& e);
	
	/// @brief Eliminates the last added entity from the Scene
	void delete_last_entity();

	/// @brief Scene getter
	/// @return Reference to the entities contained in the Scene
	const std::vector<Entity*>& get_entities() const noexcept{ return entities; };
	/// @brief Render queue getter
	/// @return Reference to the entities which are visible within the Scene
	const std::vector<Entity*>& get_visible_entities() const noexcept { return visible; };
	/// @brief Render queue getter
	/// @return Reference to the entities which are physics-enabled within the Scene
	const std::vector<Entity*>& get_physics_entities() const noexcept { return visible; };
	

	//Iterators
	std::vector<Entity*>::const_iterator begin() const noexcept { return entities.begin(); };
	std::vector<Entity*>::iterator begin()  noexcept { return entities.begin(); };

	std::vector<Entity*>::const_iterator end() const noexcept{ return entities.end(); };
	std::vector<Entity*>::iterator end() noexcept { return entities.end(); };

	//State inspectors
	
	/// @brief Size atribute
	/// @return count() of all entities of current scene
	size_t size() const noexcept { return entities.size(); };
	/// @brief Whether a scene is empty
	/// @return TRUE if empty. False otherwise
	bool  empty() const noexcept { return entities.empty();};

	/// @brief Apply physics to the elements which partake in the physics simulation
	/// @param dt amount of time since previous call
	/// @return amount of time the function needed to execute
	float update(float dt);

	/// @brief Rebuilds all the susystem queues
	void rebuild_queues();
};

