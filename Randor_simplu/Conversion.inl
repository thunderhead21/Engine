#include "Conversion.hpp"

template<typename T>
const T radians(T degrees) {
	return T(degrees * (PI / T(180)));
};