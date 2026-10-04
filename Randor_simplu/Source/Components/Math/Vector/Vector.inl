#pragma once


/*	Default 0-initializing CTOR
*/
template<class T>
inline vec<T>::vec<T>(size_t size) : size(size), data(new T[size]{ 0 }) {};

/*
*/
template<class T>
inline vec<T>::vec(std::initializer_list<T> init) : size(init.size()), data(new T[size]{ 0 }) { std::copy(init.begin(), init.end(), data); };

template<class T>
inline vec<T>::vec(const vec<T>& other) {
	size = other.size;
	data = new T[size];
	std::copy(other.data, other.data + size, data);
}


template<class T>
inline vec<T>::vec<T>(size_t size, T data) : size(size), data(new T[size](data)) {};


template<class T>
inline vec<T>::~vec()
{
	delete[] data;
}

/*	This only exists for vec2, vec3 and vec4
template<class T>
inline T& vec<T>::operator[](char dimension)
{
	return (dimension < size ? data[dimension] : throw "invalid index requested from vector");
}
*/

template<class T>
inline vec<T>& vec<T>::operator=(const vec<T> other)
{
	size = other.size;
	std::copy(other.data, other.data + size, data);

	return *this;
}

template<class T>
inline T& vec<T>::operator[](size_t position)
{
	if (position >= size) {
		throw std::out_of_range("invalid index requested from vector");
	}
	else return data[position];
}

template<class T>
inline const T& vec<T>::operator[](size_t position) const
{
	if (position >= size) {
		throw std::out_of_range("invalid index requested from vector");
	}
	else return data[position];
}

template<class T>
vec<T> vec<T>::operator+(const vec& other) const {
	
	vec<T> r(size < other.size ? other.size : size);
	size_t i = 0;

	if (other.size > size) {	//If the other vector is greater

		for ( ; i < size; i++) {		//Perform addition on the common elements
			r[i] = data[i] + other[i];
		}
		
		for (; i < other.size; i++) {		//Copy the remaining ones
			r[i] = other[i];
		}

		return r;
	}

	else if (other.size < size) {	//If this vector is greater

		for (; i < other.size; i++) {		//Perform addition on the common elements
			r[i] = other[i] + data[i];
		}

		for (; i < size; i++) {		//Copy the remaining ones
			r[i] = data[i];
		}

		return r;
	}
	else if (other.size == size) {	//If the two sizes are equal
		
		for (; i < size; i++){	//Perform addition
			r[i] = data[i] + other[i];
		}

		return r;

	}	

	return 0;
	
}

template<class T>
inline vec<T> vec<T>::operator-(const vec& other) const
{
	vec<T> r(size < other.size ? other.size : size);
	size_t i = 0;

	if (other.size > size) {	//If the other vector is greater

		for (; i < size; i++) {		//Perform subtraction on the common elements
			r[i] = data[i] - other[i];
		}

		for (; i < other.size; i++) {		//Copy the remaining ones
			r[i] = other[i];
		}

		return r;
	}

	else if (other.size < size) {	//If this vector is greater

		for (; i < other.size; i++) {		//Perform subtraction on the common elements
			r[i] = other[i] - data[i];
		}

		for (; i < size; i++) {		//Copy the remaining ones
			r[i] = data[i];
		}

		return r;
	}
	else if (other.size == size) {	//If the two sizes are equal

		for (; i < size; i++) {	//Perform subtraction
			r[i] = data[i] - other[i];
		}
		return r;
	}
	
	return 0;
}

template<class T>
inline vec<T> vec<T>::operator*(float scalar) const {
	vec<T> r{data};

	for (auto& i : r) {
		i *= scalar;
	}

	return r;

}

template<class T>
inline vec<T> vec<T>::operator*(const vec& other) const
{
	vec<T> r(size < other.size ? other.size : size);
	size_t i = 0;

	if (other.size > size) {	//If the other vector is greater

		for (; i < size; i++) {		//Perform multiplication on the common elements
			r[i] = data[i] * other[i];
		}

		for (; i < other.size; i++) {		//Copy the remaining ones
			r[i] = other[i];
		}

		return r;
	}

	else if (other.size < size) {	//If this vector is greater

		for (; i < other.size; i++) {		//Perform multiplication on the common elements
			r[i] = other[i] * data[i];
		}

		for (; i < size; i++) {		//Copy the remaining ones
			r[i] = data[i];
		}

		return r;
	}
	else if (other.size == size) {	//If the two sizes are equal

		for (; i < size; i++) {	//Perform multiplication
			r[i] = data[i] * other[i];
		}
		return r;
	}

	return 0;
}

template<class T>
inline bool vec<T>::operator==(vec& other) const {

	if (size != other.size()) return 0;
	else {
		for (size_t i = 0; i < size; i++) {

			if (data[i] != other[i]) return 0;

		}
	}


	return 1;
}