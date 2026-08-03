#include "Vector.h"

//PROVIDES IMPLEMENTATIONS OF THE MATHEMATICAL OPERATIONS

/// @brief Calculates dot product of 2 vectors
/// @param a First vector
/// @param b Second vector
/// @return Dot product of the two as float
float dot(const vec2d& a, const vec2d& b) { return (a.x * b.x + a.y * b.y); }
float dot(const vec3d& a, const vec3d& b) { return (a.x * b.x + a.y * b.y + a.z * b.z); }
float dot(const vec4d& a, const vec4d& b) { return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w); }
float dot_XYZ(const vec4d& a, const vec4d& b) { return (a.x * b.x + a.y * b.y + a.z * b.z); }


/// @brief Calculates cross product of 2 vectors
/// @param a First vector
/// @param b Second vector
/// @return Cross product of the two vectors as vec3d
vec3d cross(const vec3d& a, const vec3d& b) { return  { float((a.y * b.z) - (b.y * a.z)), float((a.z * b.x) - (b.z * a.x)), float((a.x * b.y) - (a.y * b.x)) }; }

/// @brief Calculates cross product of 2 vectors
/// @param a First vector
/// @param b Second vector
/// @return Cross product of the two as vec4d with W = 1
vec4d cross_XYZ(const vec4d& a, const vec4d& b) { return { ((a.y * b.z) - (b.y * a.z)), ((a.z * b.x) - (b.z * a.x)), ((a.x * b.y) - (a.y * b.x)), 1 }; }
/// @brief SHOULD show if all components are equal. !!TEST!!
/// @param a Vector 
/// @param b Vector
/// @return 1 if all the vector's components are equal
bool equal(const vec2d& a, const vec2d& b) { return (a.x == b.x) && (a.y == b.y); }
bool equal(const vec3d& a, const vec3d& b) { return (a.x == b.x) && (a.y == b.y) && (a.z == b.z); }
bool equal(const vec4d& a, const vec4d& b) { return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w); }

/// @brief Calculates the magnitude of vector
/// @param v Vector to calculate magnitude of 
/// @return float sqrt(A^2 + ... W^2)
float length(const vec2d& v) { return SDL_sqrtf(dot(v, v)); }
float length(const vec3d& v) { return SDL_sqrtf(dot(v, v)); }
float length(const vec4d& v) { return SDL_sqrtf(dot(v, v)); }



/// @brief Calculate length^2. Same as dot(vec)
/// @param v Vector to use
/// @return float A^2 + ... + W^2
float length_squared(const vec2d& v) { return dot(v, v); }
float length_squared(const vec3d& v) { return dot(v, v); }
float length_squared(const vec4d& v) { return dot(v, v); }

/// @brief Reduces a vector to unit or null vector
/// @param v Vector to normalize
/// @return unit vector or null vector
vec2d normalize(const vec2d& v) {
	float len = length(v);
	(len > 0.000001f);
	v* (1.0f / len);
	vec2d(0.0f);

	return vec2d({ 0.0f, 0.0f });
	
	return (len > 0.000001f) ? v * (1.0f / len) : vec2d{ 0.0f };
	
}

vec3d normalize(const vec3d& v) {
	float len = length(v);
	return (len > 0.000001f) ? v * (1.0f / len) : vec3d(0.0f);
}

vec4d normalize(const vec4d& v) {
	float len = length(v);
	return (len > 0.000001f) ? v * (1.0f / len) : vec4d{ 0 };
}


SDL_Vertex make_vertex(const vec2d& v)
{
	SDL_Vertex vertex;

		vertex.position.x = v.x;
		vertex.position.y = v.y;

	return vertex;
}

SDL_Vertex make_vertex(const vec3d& v)
{
	SDL_Vertex vertex;
	vertex.position.x = v.x;
	vertex.position.y = v.y;

	/* Do not project, just transcribe to vertex
	if (std::fabs(0 - v.z) < 0.000001f) {	//Corner case - Z = 0
		vertex.position.x = v.x;
		vertex.position.y = v.y;
	}
	else {
		vertex.position.x = v.x / v.z;
		vertex.position.y = v.y / v.z;
	}
	*/


	return vertex;
}

SDL_Vertex make_vertex(const vec4d& v)
{
	SDL_Vertex vertex;
	vertex.position.x = v.x;
	vertex.position.y = v.y;

	/* Do not project, just transcribe to vertex
	if (std::fabs(0 - v.z) < 0.000001f) {	//Corner case - Z = 0
		vertex.position.x = v.x;
		vertex.position.y = v.y;
	}
	else {
		vertex.position.x = v.x / v.z;
		vertex.position.y = v.y / v.z;
	}
	*/


	return vertex;
}

