#include "Transform.h"

mat4 Transform::matrix() const
{
	_outdated = 0;
	_matrix = (mat4::translation(_position) * (mat4::rotation(_rotation) * mat4::scale(_scale)));
	//return mat4::translation(_position) * mat4::rotation(_rotation) * mat4::scale(_scale); 
	return _matrix;
}

void Transform::position(const vec3d& position)
{
	if (position == _position) return;
	else {
		_position = position;
		_outdated = 1;
	}
}

void Transform::rotation(const vec3d& rotation)
{
	if (rotation == _rotation) return;
	else {
		_rotation = rotation;
		_outdated = 1;
	}
}

void Transform::scale(const vec3d& scale)
{
	if (scale == _scale) return;
	else {
		_scale = scale;
		_outdated = 1;
	}
}
////////////////////////// - WORLD * MESH OPERATIONS - //////////////////////////

std::vector<vec4d> Transform::operator*(const Mesh& mesh) const
{
	std::vector<vec4d> vertices_in_world;
	vertices_in_world.reserve(mesh.size());
	if(_outdated) matrix();

	for (auto &i : mesh) {
		vertices_in_world.push_back(_matrix * i);
	}
	return vertices_in_world;
}

void Transform::transform_mesh(const Mesh& mesh, std::vector<vec4d>& out) const
{
	if (_outdated) matrix();

	for (auto& vertex : mesh) {
		out.push_back(_matrix * vertex);
	}
}

void Transform::transform_mesh_batch(const Mesh* mesh_array, size_t& count, std::vector<vec4d>& out) const
{
	if (_outdated) matrix();

	for (int i = 0; i < count; i++) {
		
		for (auto &vertex : mesh_array[i]) {
			out.push_back(_matrix * vertex);
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////
Transform& Transform::operator=(const Transform& other)
{
	_outdated = 1;

	_position = other._position;
	_rotation = other._rotation;
	_scale    = other._scale;

	return *this;
}

Transform Transform::operator+(const Transform& other) const {
	return Transform({ _position + other._position }, { _rotation + other._rotation }, { _scale + other._scale });
}

Transform Transform::operator-(const Transform& other) const {
	return Transform({ _position - other._position }, { _rotation - other._rotation }, { _scale - other._scale });
}

/*
Transform& Transform::operator+=(Transform& other)
{
	return *this = *this + other;
}
*/

Transform& Transform::operator+=(const Transform& other) {
	_outdated = 1;
	return *this = *this + other;
}

Transform& Transform::operator-=(const Transform& other) {
	_outdated = 1;
	return *this = *this - other;
}

Transform Transform::operator*(const float coefficient)
{

	return Transform(_position * coefficient, _rotation * coefficient, _scale * coefficient);;
}

void Transform::operator*=(const float coefficient)
{
	_rotation *= coefficient;
	_position *= coefficient;
	_scale    *= coefficient;
}
