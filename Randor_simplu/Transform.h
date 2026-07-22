#pragma once

#include "Matrix.hpp"
#include "Mesh.h"

//Describes the object in the world - TRS
class Transform {
private:
	vec3d _position{ 0,0,0 };
	vec3d _rotation{ 0,0,0 };
	vec3d _scale{ 1,1,1 };

public:
	//Getters
	vec3d& position() { return _position; };
	vec3d& rotation() { return _rotation; };
	vec3d& scale() { return _scale; };
	mat4 matrix() const;


	//Incrementors
	void translate(const vec3d& amount) { _position += amount; };
	void rotate(const vec3d& amount) { _rotation += amount; };

	//void translate(vec3d amount) { _position += amount; };
	//void rotate(vec3d amount) { _rotation += amount; };

	//Setters
	void set_position(const vec3d& position) { _position = position; };
	void set_rotation(const vec3d& rotation) { _rotation = rotation; };
	void set_scale(const vec3d& scale) { _scale = scale; };

	std::vector<vec4d> operator*(const Mesh&  mesh);

};

