#pragma once

#include "Core.h"
#include "RigidBody.h"

/// @brief Physics solver. Instantiated by the scene implicitly
class Physics
{
private: 
	std::vector<RigidBody*> physics_space;

public:

	Physics() = default;
	

	void set_active_scene(std::vector<RigidBody*>& active_scene) { physics_space = active_scene; }

	//Iterates the active Scene [!COULD BE NULL!] and applies speeds. / Can no longer be NULL as it now owns the physics queue
	void update(float dt);
};

