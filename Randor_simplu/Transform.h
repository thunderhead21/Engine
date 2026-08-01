#pragma once

#include "Matrix.hpp"
#include "Mesh.h"

//Describes the object in the world - TRS

/// @brief Describes the object in the world - TRS. Rotation and position set to 0 by default. Scale to 1.

// [ARCHITECTURE]
// ==========================================================
// ARCHITECTURAL INVARIANT
//
// Transform is the only authoritative spatial state.
//
// If another class begins storing independent position,
// rotation or scale, the ownership model has been broken.
//
// Avoid synchronization.
// Prefer one truth.
// 
// ==========================================================
// 
// Mesh never owns position, rotation or scale.
// Rendering always consumes Entity::Transform.

// [DESIGN]
// Scale belongs to Transform.
//
// Physics may consume scale (for collision volumes),
// but Transform remains the authoritative owner.

class Transform {
private:
	vec3d _position{ 0,0,0 };
	vec3d _rotation{ 0,0,0 };
	vec3d _scale{ 1,1,1 };

public:

	Transform() : _position({ 0,0,0 }), _rotation({ 0,0,0 }), _scale({1,1,1}) {};
	Transform(vec3d position, vec3d rotation, vec3d scale) : _position(position), _rotation(rotation), _scale(scale) {};

	//Getters
	vec3d& position() { return _position; };
	vec3d& rotation() { return _rotation; };
	vec3d& scale() { return _scale; };
	mat4 matrix() const;

	const vec3d& position() const { return _position; };
	const vec3d& rotation() const { return _rotation; };
	const vec3d& scale() const { return _scale; };


	//Incrementors
	void translate(const vec3d& amount) { _position += amount; };
	void rotate(const vec3d& amount) { _rotation += amount; };

	//void translate(vec3d amount) { _position += amount; };
	//void rotate(vec3d amount) { _rotation += amount; };

	//Setters
	void position(const vec3d& position) { _position = position; };
	void rotation(const vec3d& rotation) { _rotation = rotation; };
	void scale(const vec3d& scale) { _scale = scale; };

	std::vector<vec4d> operator*(const Mesh&  mesh) const;
	Transform& operator=(const Transform& other);

	Transform operator+(const Transform& other) const;
	Transform operator-(const Transform& other) const;
	Transform& operator+=(const Transform& other);
	Transform& operator-=(const Transform& other);

	Transform operator*(const float coefficient);


};

