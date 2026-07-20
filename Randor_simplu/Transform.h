#pragma once

#include "Matrix.hpp"

//Describes the object in the world - TRS
class Transform {
private:
	vec3d _position;
	vec3d _rotation;
	vec3d _scale;

public:
	//Getters
	vec3d& position() { return _position; };
	vec3d& rotation() { return _rotation; };
	vec3d& scale() { return _scale; };
	mat4 matrix() const { 
		auto t = mat4::translation(_position);
		auto r = mat4::rotation(_rotation);
		auto s = mat4::scale(_scale);
		//return mat4::translation(_position) * mat4::rotation(_rotation) * mat4::scale(_scale); 
		return (t * (r * s));
	} ;


	//Incrementors
	void translate(const vec3d& amount) { _position += amount; };
	void rotate(const vec3d& amount) { _rotation += amount; };

	//void translate(vec3d amount) { _position += amount; };
	//void rotate(vec3d amount) { _rotation += amount; };

	//Setters
	void set_position(const vec3d& position) { _position = position; };
	void set_rotation(const vec3d& rotation) { _rotation = rotation; };
	void set_scale(const vec3d& scale) { _scale = scale; };



};

