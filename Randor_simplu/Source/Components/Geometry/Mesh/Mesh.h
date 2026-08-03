#pragma once

#include <vector>
#include "../../Math/Vector/Vector.h"

// [ARCHITECTURE]
// Transform is the single source of truth for spatial state.
//
// Mesh never owns position, rotation or scale.
// Rendering always consumes Entity::Transform.


struct Mesh {
protected:
	std::vector<vec3d> _vertices;	//The points in space
	std::vector<uint32_t> _indices;	///The order in which to draw the lines between them

	/// @brief Add a triangle to the mesh
	/// @param A, B, C - Local coordinates of the triangle vertices
	void append_triangle(const vec3d& a, const vec3d& b, const vec3d& c);
	void append_quad(const vec3d& a, const vec3d& b, const vec3d& c, const vec3d& d);

public:

	//    |-----------------Auto------------------|
	inline std::vector<vec3d>::iterator begin() noexcept { return _vertices.begin(); }
	inline std::vector<vec3d>::iterator end() noexcept { return _vertices.end(); }

	inline std::vector<vec3d>::const_iterator begin()const noexcept { return _vertices.begin(); }
	inline std::vector<vec3d>::const_iterator end() const noexcept { return _vertices.end(); }
	
	inline size_t size() const  noexcept { return _vertices.size(); }


	inline std::vector<vec3d>& vertices() noexcept { return _vertices; }
	inline std::vector<uint32_t>& indices() noexcept { return _indices; }
};
