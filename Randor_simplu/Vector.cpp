#include "Vector.h"

// PROVIDES FUNCTION IMPLEMENTATIONS FOR VECXD MEMBERS

/// @brief Returns SIMD vectorial sumcomponent
/// @param other - vector to add
/// @return 

/* SIMD optimized code for the vector class
vec2_simd vec2_simd::operator+(const vec2_simd& other) const
{
	return _mm_add_ps(data, other.data);
}

vec2_simd vec2_simd::operator-(const vec2_simd& other) const
{
	return _mm_sub_ps(data, other.data);
}

vec2_simd vec2_simd::operator*(__m128 scalar) const
{
	
	return _mm_mul_ps(data, scalar);
}

vec2_simd vec2_simd::operator*(const float& scalar) const
{

	__m128 s = _mm_set1_ps(scalar);

	return { _mm_mul_ps(data, s) };
}
*/

vec2d vec2d::operator+(const vec2d& other) const
{
	return { x + other.x, y + other.y };
}
vec2d vec2d::operator-(const vec2d& other) const
{
	return { x - other.x, y - other.y };
}
vec2d vec2d::operator*(const float scalar) const
{
	return { scalar * x, scalar * y };
}
float& vec2d::operator[](char dimension) 
{
	switch (SDL_tolower(dimension)) {
	case 'x': return x;
	case 'y': return y;
	default: throw "invalid dimension: " + dimension;

	}
}
/* OBSOLETE - Prefer Character index over enum class Axis
float& vec2d::operator[](Axis axis) {
	switch (axis) {
	case Axis::X: return x;
	case Axis::Y: return y;
	case Axis::Z: throw "Invalid axis requested! No Z in Vec2D";
	case Axis::W: throw "Invalid axis requested! No Z in Vec2D";

	}
}
*/

vec3d vec3d::operator+(const vec3d& other) const
{
	return { x + other.x, y + other.y, z + other.z};
}
vec3d vec3d::operator-(const vec3d& other) const
{
	return { x - other.x, y - other.y, z - other.z };
}
vec3d vec3d::operator*(const float scalar) const
{
	return { scalar * x, scalar * y, scalar * z };
}
void vec3d::operator+=(const vec3d& other)
{
	x += other.x;
	y += other.y;
	z += other.z;

}
float& vec3d::component(char component){
	switch (SDL_tolower(component)) {
	case 'x': return x;
	case 'y': return y;
	case 'z': return z;
	default: throw "invalid component: " + component;

	}
}
const float& vec3d::component(char component) const {
	switch (SDL_tolower(component)) {
	case 'x': return x;
	case 'y': return y;
	case 'z': return z;
	default: throw "invalid component: " + component;

	}
}

float& vec3d::operator[](size_t dimension)
{
	switch (dimension) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default: throw "invalid dimension: " + dimension;

	}
}

const float& vec3d::operator[](size_t dimension) const
{
	switch (dimension) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default: throw "invalid dimension: " + dimension;

	}
}



SDL_Vertex vec2d::vertex() const
{
	/////  Shallow copy pass-by-value due to member not allowing const [non-altering] member and pass by reference 
	return make_vertex(*this);
}

SDL_Vertex vec3d::vertex() const
{
	/////  Shallow copy pass-by-value due to member not allowing const [non-altering] member and pass by reference 
	return make_vertex(*this);
}

SDL_Vertex vec4d::vertex() const
{
	/////  Shallow copy pass-by-value due to member not allowing const [non-altering] member and pass by reference 
	return SDL_Vertex({x, y});
}

/* OBSOLETE - Prefer Character index over enum class Axis
float& vec3d::operator[](Axis axis) {
	switch (axis) {
	case Axis::X: return x;
	case Axis::Y: return y;
	case Axis::Z: return z;
	case Axis::W: throw "Invalid axis requested! No W in Vec3D";

	}
}
*/
vec4d vec4d::operator+(const vec4d& other) const
{
	return { x + other.x, y + other.y, z + other.z, w};
}
vec4d vec4d::operator-(const vec4d& other) const
{
	return { x - other.x, y - other.y, z - other.z, w};
}
vec4d vec4d::operator*(const float scalar) const
{
	return { scalar * x, scalar * y, scalar * z, w};
}
const float& vec4d::operator[](char dimension) const {
	switch (SDL_tolower(dimension)) {
	case 'x': return x;
	case 'y': return y;
	case 'z': return z;
	case 'w': return w;
	default: throw "invalid dimenion " + dimension;

	}
}
float& vec4d::operator[](char dimension) {
	switch (SDL_tolower(dimension)) {
	case 'x': return x;
	case 'y': return y;
	case 'z': return z;
	case 'w': return w;
	default: throw "invalid dimenion " + dimension;
	}
}

float& vec4d::operator[](int dimension)
{
	if (dimension >= 4) throw "invalid dimenion " + dimension;
	
	switch (dimension) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	}
}

const float& vec4d::operator[](int dimension) const
{
	if (dimension >= 4) throw "invalid dimenion " + dimension;

	switch (dimension) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	}
}
#include <string>

std::ostream& operator<<(std::ostream& os, const vec4d& v) {
	os << v.x << " " << v.y << " " << v.z << " " << v.w;
	return os;
}