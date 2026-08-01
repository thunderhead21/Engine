#include "Mesh.h"


void Mesh::append_triangle(const vec3d& a, const vec3d& b, const vec3d& c) {
	uint32_t i = _vertices.size();

	_vertices.push_back(a);
	_vertices.push_back(b);
	_vertices.push_back(c);

	
	_indices.push_back(i + 0);
	_indices.push_back(i + 1);
	_indices.push_back(i + 2);
}

void Mesh::append_quad(const vec3d& a, const vec3d& b, const vec3d& c, const vec3d& d) {
	uint32_t i = _vertices.size();
	
	_vertices.push_back(a);
	_vertices.push_back(b);
	_vertices.push_back(c);
	_vertices.push_back(d);


	_indices.push_back(i + 0);
	_indices.push_back(i + 1);
	_indices.push_back(i + 2);

	_indices.push_back(i + 0);
	_indices.push_back(i + 2);
	_indices.push_back(i + 3);
}
