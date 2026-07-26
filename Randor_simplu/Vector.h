#pragma once

#include <immintrin.h>
#include <ostream>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_ttf/SDL_textengine.h>
#include <spdlog/spdlog.h>


///////////////////////////////////////////// DISAMBIGUATION /////////////////////////////////////////////
//
// Math.cpp - Provide vector members implementation for operators [+, -, *]
// Vector_math - Provides non-member implementations [dot(), cross, length]
//


/*
	SIMD:

	immintrin is the only SIMD header needed but will require all CPU Extensions

	<mmintrin.h>  MMX
	<xmmintrin.h> SSE
	<emmintrin.h> SSE2
	<pmmintrin.h> SSE3
	<tmmintrin.h> SSSE3
	<smmintrin.h> SSE4.1
	<nmmintrin.h> SSE4.2
	<ammintrin.h> SSE4A
	<wmmintrin.h> AES
	<immintrin.h> AVX, AVX2, FMA

	This may still be useful with MSVC and ICC to stop yourself from using instruction-sets you don't want to require

	enum class Axis : char {
	X,
	Y,
	Z,
	W
};	  --Deprecated in favour of vecxd::operator[](char dimension);
*/

/////////////////////////// PROTOTYPES ///////////////////////////

struct vec2d; ///
struct vec3d; ///	Necessary for function prototypes
struct vec4d; ///

float dot(const vec2d& a, const vec2d& b);
float dot(const vec3d& a, const vec3d& b);
float dot(const vec4d& a, const vec4d& b);
float dot_XYZ(const vec4d& a, const vec4d& b);

float length(const vec2d& v);
float length(const vec3d& v);
float length(const vec4d& v);

float length_squared(const vec2d& v);
float length_squared(const vec3d& v);
float length_squared(const vec4d& v);

bool equal(const vec2d& a, const vec2d& b);
bool equal(const vec3d& a, const vec3d& b);
bool equal(const vec4d& a, const vec4d& b);

vec2d normalize(const vec2d& v);
vec3d normalize(const vec3d& v);
vec4d normalize(const vec4d& v);

SDL_Vertex make_vertex(const vec2d& v);
SDL_Vertex make_vertex(const vec3d& v);





/*		--SIMD optimized vector classes. As per YAGNI, they are not needed (yet)
struct alignas(16) vec2_simd {		//2 x double
	__m128 data;

	vec2_simd() : data(_mm_setzero_ps()) {}
	vec2_simd(__m128 v) : data(v) {}

	
	float& operator[](char dimension);
	const float& operator[](char dimension) const;

	vec2_simd operator+(const vec2_simd& other) const;
	vec2_simd operator-(const vec2_simd& other) const;
	vec2_simd operator*(__m128 scalar) const;
	vec2_simd operator*(const float& scalar) const;

};

struct alignas(64) vec4_simd {		//Float 
	__m128 data;

	vec4_simd() : data(_mm_setzero_ps()) {}
};
*/

/// @brief 2 Dimensional vector with float X Y members
struct vec2d {
	float x, y;	

	float& operator[](char dimension);
	vec2d operator+(const vec2d& other) const;
	vec2d operator-(const vec2d& other) const;
	vec2d operator*(float scalar) const;
	inline bool operator==(vec2d& other) const { return equal(*this, other); };


	inline float magnitude() const { return length(*this); }
	inline float magnitude_square() const { return length_squared(*this); }
	inline vec2d normalized()const { return normalize(*this); }
	SDL_Vertex vertex() const;


	vec2d() = default;
	vec2d(const float& xy) : x(xy), y(xy) {};
	vec2d(float x, float y) : x(x), y(y) {};
	vec2d(const vec2d& other) : x(other.x), y(other.y) {};

	friend std::ostream& operator<<(std::ostream& os, const vec2d& v);

};

/// @brief 3 Dimensional vector with float X Y Z members
struct vec3d {
	float x, y, z;

	float& component(char component);
	const float& component(char component) const;
	
	float& operator[](size_t dimension);
	const float& operator[](size_t dimension) const;

	vec3d operator+(const vec3d& other) const;
	vec3d operator-(const vec3d& other) const;
	vec3d operator*(float scalar) const;
	inline bool operator==(vec3d& other) const { return equal(*this, other); };
	void operator+=(const vec3d& other);

	inline float magnitude() const { return length(*this); }
	inline float magnitude_square() const { return length_squared(*this); }
	inline vec3d normalized() const { return normalize(*this); }
	SDL_Vertex vertex() const;

	/// @brief Default constructor
	vec3d() :x(0), y(0), z(0) {};

	/// @brief Constructor for the entire vector
	/// @param x component to initialize the vector
	/// @param y component to initialize the vector
	/// @param z component to initialize the vector
	vec3d(const float& x, const float& y, const float& z) :x(x), y(y), z(z) {};

	/// @brief Uniform constructor
	/// @param xyz Value to initialize all the components with
	vec3d(const float& xyz) : x(xyz), y(xyz), z(xyz) {};

	/// @brief Copy constructor
	/// @param other vector to copy
	vec3d(const vec3d& other) : x(other.x), y(other.y), z(other.z) {};

	/// @brief Obtain the X and Y components of the vector
	/// @return vec2d populated with the X and Y components
	inline vec2d xy() const { return { x, y }; };

	/// @brief Obtain the X, Y and Z components of the vector
	/// @return vec2d populated with the X, Y and Z components 
	inline vec3d xyz() const { return { x,y,z }; };

	friend std::ostream& operator<<(std::ostream& os, const vec3d& v);
};

/// @brief 4 Dimensional vector with float X Y Z W members. W = 0 if the vector represents a direction. W = 1 if the vector represents a position.
struct vec4d {
	float x, y, z, w;

	float& operator[](char dimension);
	const float& operator[](char dimension) const;
	float& operator[](int dimension);
	const float& operator[](int dimension) const;

	vec4d operator+(const vec4d& other) const;
	vec4d operator-(const vec4d& other) const;
	vec4d operator*(float scalar) const;
	inline bool operator==(vec4d& other) const { return equal(*this, other); };

	inline float magnitude() const { return length(*this); }
	inline float magnitude_square() const { return length_squared(*this); }
	inline vec4d normalized() const { return normalize(*this); }
	SDL_Vertex vertex() const;

	inline vec4d() = default;
	//Only initializer list is needed
	inline vec4d(const float& xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {};
	inline vec4d(const float& x, const float& y, const float& z, const float& w) :x(x), y(y), z(z), w(w) {};	
	inline vec4d(const vec4d& other) : x(other.x), y(other.y), z(other.z), w(other.w) {};
	
	inline vec2d xy() const { return { x, y }; };
	inline vec3d xyz() const { return {x, y, z}; }
	///////////////////////////WORKSPACE///////////////////////////////
	//inline void print() const { std::cout << x << ', ' << y << ', ' << z << ', ' << w << ', ' ; };
	friend std::ostream& operator<<(std::ostream& os, const vec4d& v);
	
};

inline vec3d from(const vec2d& v, const float& z) { return { v.x, v.y, z }; };
inline vec4d from(const vec2d& v, const float& z, const float& w) { return { v.x, v.y, z, w }; };
inline vec4d from(const vec3d& v, const float& w) { return { v.x, v.y, v.z, w }; };



/*
Data Type	Minimum Size (Bits)	Typical Size (Bytes)
char				8				1
short				16				2
int					16				4
long				32				4 (32-bit) or 8 (64-bit Linux/macOS)
long long			64				8
float				32				4
double				64				8
bool				8				1
*/