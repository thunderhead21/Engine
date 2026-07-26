#include "Projection.h"


SDL_Vertex flat_projection(const vec3d& v) {
	SDL_Vertex vertex;

	vertex.position.x = v.x;
	vertex.position.y = v.y;

	return vertex;
}

SDL_Vertex weak_projection(vec2d window_dimensions, const vec3d& v) {
	SDL_Vertex vertex;


	float camera = 2000.0f;
	float focal = 500.0f;
	
	/*
	vertex.position.x = fabs(v.z - 0) <= 0.00001 ? v.x : v.x / v.z;
	vertex.position.y = fabs(v.z - 0) <= 0.00001 ? v.y : v.y / v.z;
	*/

	float z = v.z + camera;
	if (z <= 1.0f) z = 1.0f;

	vertex.position.x = (window_dimensions.x * 0.5f) + (focal * v.x / z);
	vertex.position.y = (window_dimensions.y * 0.5f) - focal * v.y / z;



	return vertex;
}