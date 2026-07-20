#include "Weak_Perspective_Projection.h"

/// @brief 3D point to weakly project into a vertex by dividing X and Y by Z.
/// @param v - Vec3d corresponding to the point to project
/// @return The resulting SDL_Vertex
SDL_Vertex weak_projection(vec3d& v) {
	return { v.x / v.z, v.y / v.z };
}