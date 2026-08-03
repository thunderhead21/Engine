#pragma once

#include <cassert>
#include <vector>
#include <set>
#include <iostream>
#include <iomanip>
#include <math.h>

#include "../Components/Math/Vector/Vector.h"
#include "../Core/Timer/Timer.h"

using Watch = std::chrono::steady_clock;
const float EPS = std::numeric_limits<float>::epsilon();
constexpr int QUIET = 1;

/*

The tests return 1 on success
0 on failure.

*/
bool TEST_vec2d_length();
bool TEST_vec3d_length();
bool TEST_vec4d_length();

bool TEST_vec2d_square();
bool TEST_vec3d_square();
bool TEST_vec4d_square();

bool TEST_vec2d_vertex();
bool TEST_vec3d_vertex();
bool TEST_vec4d_vertex();

void TEST_platform_scheduler_precision(unsigned int duration, unsigned int iterations);