#pragma once
#include "Vector.h"
#include "Matrix.hpp"

//This is the real deal. You need matrix and vector multiplications
vec4d perspective_projection();

//Does not project in any way. Serves as a plain cast to vertex
SDL_Vertex flat_projection(const vec3d& v);



//
SDL_Vertex weak_projection(const vec3d& v);