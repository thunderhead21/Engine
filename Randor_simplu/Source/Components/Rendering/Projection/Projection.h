#pragma once

#include "Window.h"
//This is the real deal. You need matrix and vector multiplications
vec4d perspective_projection();

//Divides the X and Y components by Z
SDL_Vertex weak_projection(vec2d window_dimensions, const vec3d& v);
void weak_projection(vec2d window_dimensions, const vec3d& v, std::vector<SDL_Vertex>& out);

//Does not project in any way. Serves as a plain cast to vertex
SDL_Vertex flat_projection(const vec3d& v);