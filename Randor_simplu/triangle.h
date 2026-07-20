#pragma once
#include "vector.h"
#include "Mesh.h"

struct triangle : Mesh {
	vec3d points[3];	//The three points of the triangle

	inline vec3d* begin() noexcept { return &points[0]; }	//First point
	inline vec3d* end() noexcept { return &points[3]; }		//Past last point [Required]

	vec3d* to_tris() { return points; }

};

