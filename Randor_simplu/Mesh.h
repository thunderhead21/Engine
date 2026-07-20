#pragma once

#include <vector>

#include "triangle.h"
#include "rectangle.h"

struct Mesh {
	std::vector<SDL_Vertex> vertices;
	std::vector<uint32_t> indices;

	//         |-----------------Auto------------------|
	inline std::vector<SDL_Vertex>::iterator begin() noexcept { return vertices.begin(); }
	inline std::vector<SDL_Vertex>::iterator end() noexcept { return vertices.end(); }
	inline std::vector<SDL_Vertex>& get_vertices() noexcept { return vertices; }
	inline std::vector<uint32_t>& get_indices() noexcept { return indices; }
};
