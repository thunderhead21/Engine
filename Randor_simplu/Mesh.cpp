#include "Mesh.h"


void Mesh::append_triangle(const vec3d& a, const vec3d& b, const vec3d& c) {
	uint32_t i = vertices.size();

	vertices.push_back(a);
	vertices.push_back(b);
	vertices.push_back(c);

	
	indices.push_back(i + 0);
	indices.push_back(i + 1);
	indices.push_back(i + 2);
}

void Mesh::append_quad(const vec3d& a, const vec3d& b, const vec3d& c, const vec3d& d) {
	uint32_t i = vertices.size();
	
	vertices.push_back(a);
	vertices.push_back(b);
	vertices.push_back(c);
	vertices.push_back(d);


	indices.push_back(i + 0);
	indices.push_back(i + 1);
	indices.push_back(i + 2);

	indices.push_back(i + 0);
	indices.push_back(i + 2);
	indices.push_back(i + 3);
}
