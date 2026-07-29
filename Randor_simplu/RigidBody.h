#pragma once
#include "Entity.h"

/// @brief A physics-enabled entity in the world. Updated by the Physics engine
class RigidBody : public Entity
{
protected:
	friend class Physics;

	bool physics_enabled{ 1 };

	vec3d velocity;
	vec3d angular_velocity;

	float mass{ 1.0f };


public:

	//CTOR
	RigidBody();
	RigidBody(Mesh mesh);
	~RigidBody() = default;

	//Setters
	void set_mass(float mass) { mass = mass; }
	void set_velocity(vec3d speed) { velocity = speed; };
	void set_angular_velocity(vec3d ang_speed) { angular_velocity = ang_speed; };

	float get_mass() { return mass; }
	vec3d get_velocity() { return velocity; };
	vec3d get_angular_velocity() { return angular_velocity; };

	bool is_simulated() const { return physics_enabled; };
	bool toggle_physics() { physics_enabled = physics_enabled; return physics_enabled; };

	void disable_physics() { physics_enabled = false; };
	void enable_physics() { physics_enabled = true; };



	/////////////////FACTORIES/////////////////
	static RigidBody Cube(float side = 400);
	static RigidBody Rectangle(float width = 300, float height = 150);
	static RigidBody Triangle(float width = 300, float height = 300);
};