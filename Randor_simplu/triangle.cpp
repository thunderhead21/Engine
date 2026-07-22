#include "triangle.h"

triangle::triangle(const vec3d& a, const vec3d& b, const vec3d& c) {
	vertices = { a, b, c };
	indices = { 0, 1, 2 };
}