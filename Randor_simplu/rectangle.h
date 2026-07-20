#pragma once
#include <vector>
#include "Mesh.h"

struct rectangle : public Mesh {
	float x, y, z; //Center position
	float w, h, d; //Width, height, and SUPPOSED dZ

	std::vector<triangle> to_tris() const;

};
