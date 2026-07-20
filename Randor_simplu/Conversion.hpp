#pragma once

#include "Constants.h"

template<typename T>
const T radians(T degrees) {
	return T(degrees * (PI / T(180)));
};

#include "Conversion.hpp"