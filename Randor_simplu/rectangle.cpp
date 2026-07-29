#include "rectangle.h"

/*
std::vector<SDL_Vertex> Rectangle::to_tris() const {
	//KEEP THE TRIGONOMETRIC ORDER
	
	//Remove intrinsic projection

	//Top left
	vec3d p1 = { x - (w / 2), y - (h / 2), z - (d / 2) };
	//Down Left --- p1 is perpendicular to p2
	vec3d p2 = { x - (w / 2), y + (h / 2), z - (d / 2) };
	//Down Right
	vec3d p3 = { x + (w / 2), y + (h / 2), z + (d / 2) };
	//Up Right
	vec3d p4 = { x + (w / 2), y - (h / 2), z + (d / 2) };

	return { { p1, p2, p4 }, {p2, p3, p4} };



}
*/

Rectangle::Rectangle(float width, float height) {
	float hx = width * 0.5f;
	float hy = height * 0.5f;

	vertices = {
		{-hx, -hy, 0},
		{-hx,  hy, 0},
		{ hx,  hy, 0},
		{ hx, -hy, 0}
	};

	indices = {
		0, 1, 2,
		0, 2, 3
	};

}

Rectangle::Rectangle(vec3d& a, vec3d& b, vec3d& c, vec3d& d) {

	vertices = { a, b, c, d };

	indices = {
		0, 1, 2,
		2, 3, 0
	};

}