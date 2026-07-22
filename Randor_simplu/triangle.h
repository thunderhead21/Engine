#pragma once
#include "vector.h"
#include "Mesh.h"

class triangle : public Mesh {
public:
	triangle(const vec3d& a, const vec3d& b, const vec3d& c);

};

