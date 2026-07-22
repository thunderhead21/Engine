#include "Projection.h"
SDL_Vertex flat_projection(const vec3d& v) {
	SDL_Vertex vertex;

	vertex.position.x = v.x;
	vertex.position.y = v.y;

	return vertex;
}

SDL_Vertex weak_projection(const vec3d& v) {
	SDL_Vertex vertex;

	vertex.position.x = fabs(v.z - 0) <= 0.00001 ? v.x : v.x / v.z;
	vertex.position.y = fabs(v.z - 0) <= 0.00001 ? v.y : v.y / v.z;;

	return vertex;
}