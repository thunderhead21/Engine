#include "Transform.h"

mat4 Transform::matrix() const
{
	auto t = mat4::translation(_position);
	auto r = mat4::rotation(_rotation);
	auto s = mat4::scale(_scale);

	//return mat4::translation(_position) * mat4::rotation(_rotation) * mat4::scale(_scale); 
	return (t * (r * s));
}

std::vector<vec4d> Transform::operator*(const Mesh& mesh)
{
	std::vector<vec4d> vertices_in_world;
	vertices_in_world.reserve(mesh.size());

	mat4 trans_mat = matrix();
	for (auto &i : mesh) {
		vertices_in_world.push_back(trans_mat * i);
	}

	return vertices_in_world;
}
