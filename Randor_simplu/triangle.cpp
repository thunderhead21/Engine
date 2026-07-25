#include "triangle.h"

Triangle::Triangle(const vec3d& a, const vec3d& b, const vec3d& c) {
	vertices = { a, b, c };
	indices = { 0, 1, 2 };
}

Triangle::Triangle(const float& width, const float& height) {
	
	float x = width * 0.5f;
	float y = height * 0.5f;

	vertices = { 
		{-x, -y, 0},
		{x , -y, 0},
		{0 ,  y, 0}
	};
	indices = { 0, 1, 2 };
}

Triangle Triangle::Equilateral(const float& side) {

	float h = side * std::sqrt(3.0f) * 0.5f;

	return Triangle(
		{ -side * 0.5f, -h / 3.0f, 0 },
		{ side * 0.5f, -h / 3.0f, 0 },
		{ 0.0f , 2.0f * h / 3.0f, 0 }
	);
	
} 

Triangle Triangle::Isosceles(const float& base, const float& height) {
	float hb = base * 0.5f;
	float hh = height * 0.5f;

	return Triangle(
		{ -hb, -hh, 0 },
		{ hb, -hh, 0 },
		{ 0 ,  hh, 0 }
	);
	
}

Triangle Triangle::Right(const float& width, const float& height) {
	float hw = width * 0.5f;
	float hh = height * 0.5f;

	return Triangle(
		{ -hw, -hh, 0 },
		{ hw, -hh, 0 },
		{ hw,  hh, 0 }
	);
	
}