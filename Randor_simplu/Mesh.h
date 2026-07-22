#pragma once

#include <vector>
#include "Vector.h"

struct Mesh {
protected:
	std::vector<vec3d> vertices;
	std::vector<uint32_t> indices;

public:

	//    |-----------------Auto------------------|
	inline std::vector<vec3d>::iterator begin() noexcept { return vertices.begin(); }
	inline std::vector<vec3d>::iterator end() noexcept { return vertices.end(); }

	inline std::vector<vec3d>::const_iterator begin()const noexcept { return vertices.begin(); }
	inline std::vector<vec3d>::const_iterator end() const noexcept { return vertices.end(); }
	
	inline size_t size() const  noexcept { return vertices.size(); }


	inline std::vector<vec3d>& get_vertices() noexcept { return vertices; }
	inline std::vector<uint32_t>& get_indices() noexcept { return indices; }
};
