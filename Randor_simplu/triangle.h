#pragma once
#include "vector.h"
#include "Mesh.h"

class Triangle : public Mesh {
public:
	Triangle(const vec3d& a, const vec3d& b, const vec3d& c);
	Triangle(const float& width, const float& height);
	Triangle() = default;

	static Triangle Equilateral(const float& side);
	static Triangle Isosceles(const float& base, const float& height);
	static Triangle right(const float& width, const float& height);
};

