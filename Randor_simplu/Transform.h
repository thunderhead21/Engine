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

//TIP - Non-const function should _probably_ set _outdated = 1;

class Transform {
private:
	vec3d _position{ 0,0,0 };
	vec3d _rotation{ 0,0,0 };
	vec3d _scale{ 1,1,1 };

	mutable mat4 _matrix;
	mutable bool _outdated{1};	//Rebuild Matrix cache ASAP flag

public:

	Transform() : _position({ 0,0,0 }), _rotation({ 0,0,0 }), _scale({1,1,1}) {};
	Transform(vec3d position, vec3d rotation, vec3d scale) : _position(position), _rotation(rotation), _scale(scale) {};

	//Getters
	vec3d& position() { return _position; _outdated = 1; };
	vec3d& rotation() { return _rotation; _outdated = 1; };
	vec3d& scale() { return _scale; _outdated = 1; };
	mat4 matrix() const;

	const vec3d& position() const { return _position; };
	const vec3d& rotation() const { return _rotation; };
	const vec3d& scale() const { return _scale; };

	bool changed() const { return _outdated; };

	//Incrementors
	void translate(const vec3d& amount) { _position += amount; _outdated = 1; };
	void rotate(const vec3d& amount) { _rotation += amount; _outdated = 1; };

	//void translate(vec3d amount) { _position += amount; };
	//void rotate(vec3d amount) { _rotation += amount; };

	//Setters
	void position(const vec3d& position);
	void rotation(const vec3d& rotation);
	void scale(const vec3d& scale);

	/// @brief Transform the mesh from local coordinates to world coordinates coordinates.
	/// @brief That means it places the entity's representation in the world
	/// @brief SUB-OPTIMAL! USE OPTIMIZED transform_mesh() !
	/// @param mesh - the mesh to apply the transformation to.
	/// @return std::vector containing the resulting vertices as vec4
	std::vector<vec4d> operator*(const Mesh&  mesh) const;
	/// @brief Transform the mesh from local coordinates to world coordinates coordinates.
	/// @brief That means it places the entity's representation in the world
	/// @param mesh - the mesh to apply the transformation to.
	/// @param out - reference to the storage buffer
	void transform_mesh(const Mesh& mesh, std::vector<vec4d>& out) const;
	/// @brief Transform the provided meshes from local coordinates to world coordinates coordinates.
	/// @brief That means it places the entity's representation in the world
	/// @param mesh - the mesh array to apply the transformation to.
	/// @param count - number of meshes to transform
	/// @param out - reference to the storage buffer
	void transform_mesh_batch(const Mesh* mesh_array, size_t& count, std::vector<vec4d>& out) const;


	Transform& operator=(const Transform& other);

	Transform operator+(const Transform& other) const;
	Transform operator-(const Transform& other) const;
	Transform& operator+=(const Transform& other);
	Transform& operator-=(const Transform& other);

	Transform operator*(const float coefficient);
	void operator*=(const float coefficient);

};

