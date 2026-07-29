#pragma once

#include "Core.h"
#include "RigidBody.h"

class Physics
{
private: 
	std::vector<RigidBody*> physics_space;

public:

	Physics() = default;
	

	void set_active_scene(std::vector<RigidBody*>& active_scene) { physics_space = active_scene; }

	//Iterates the active Scene [!COULD BE NULL!] and applies speeds.
	void update(float dt);
};

