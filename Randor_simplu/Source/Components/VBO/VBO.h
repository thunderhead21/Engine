#pragma once

#include "Components/Math/Vector/Vector.h"

/// @brief Vertex Buffer Object
class VBO {
private:
	std::vector<vec4d> _world_cache{};
	std::vector<SDL_Vertex> _projection_cache{};

public:
	std::vector<SDL_Vertex>& projection_buffer() { return _projection_cache; }
	std::vector<vec4d>& world_buffer() { return _world_cache; }

	VBO() = default;
	~VBO() = default;
};