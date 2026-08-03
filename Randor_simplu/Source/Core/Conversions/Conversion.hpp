#pragma once


template<typename T>
const T radians(T degrees) {
	return T(degrees * (PI / T(180)));
};

#include "Conversion.hpp"