#pragma once

#if POD_VECTOR == 0
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
inline vec<T>& vec<T>::operator=(const vec<T>& other)
{
	if (this == &other) return *this;
	if(data != nullptr) delete[] data;

	size = other.size;		
	data = new T[size];

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
inline vec<T> vec<T>::operator+(const vec& other) const {
	
	const size_t result_size = std::max(size, other.size);
	vec<T> r(result_size);
	size_t i = 0;

	for (int i = 0; i < result_size; i++) {
		const T lhs = i < size ? data[i] : T{};
		const T rhs = i < other.size ? other[i] : T{};

		r[i] = lhs + rhs;
	}

	return r;
	
}

template<class T>
inline vec<T> vec<T>::operator-(const vec& other) const
{
	const size_t result_size = std::max(size, other.size);
	vec<T> r(result_size);
	size_t i = 0;
	
	for (int i = 0; i < result_size; i++) {
		const T lhs = i < size ? data[i] : T{};
		const T rhs = i < other.size ? other[i] : T{};

		r[i] = lhs - rhs;
	}

	return r;
	
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
	const size_t result_size = std::max(size, other.size);
	vec<T> r(result_size);
	size_t i = 0;

	for (int i = 0; i < result_size; i++) {
		const T lhs = i < size ? data[i] : T{};
		const T rhs = i < other.size ? other[i] : T{};

		r[i] = lhs * rhs;
	}

	return r;
}

template <class T>
inline vec<T> vec<T>::operator-() const {

	vec<T> r;

	for (size_t i = 0; i < size; i++) {
		r[i] = -data[i];
	}

	return r;
};

template<class T>
inline bool vec<T>::operator==(const vec<T>& other) const {

	if (size != other.size) return 0;
	else {
		for (size_t i = 0; i < size; i++) {

			if (data[i] != other[i]) return 0;

		}
	}


	return 1;
}


template<class T>
inline double vec<T>::length() {

	double squares = 0.0;

	for (auto& i : *this) {
		squares += i * i;
	}

	return sqrt(squares);

};


template<class T>
inline vec<T> vec<T>::normalized() const {
	vec<T> r{ data };
	double epsilon = 0.000001f;

	if (length() <= epsilon) return vec<T>(size);
	for (auto& i : r) {

		i *= 1 / length();
	}


};

template<class T>
inline vec<T> vec<T>::normalized(double epsilon) const {

	vec<T> r{ data };

	if (length() <= epsilon) return vec<T>(size);
	for (auto& i : r) {

		i *= 1 / length();
	}

}

template<class T>
inline size_t vec<T>::append(const T& elem) {
	size = size + 1;
	T* container = new T[size];

	for (size_t i = 0; i < size - 1; i++) {
		container[i] = data[i];
	}

	container[size - 1] = elem;
	delete[] data;

	data = container;

	return size;

}

/*
template<class T>
size_t vec<T>::append(T elem) {
	size = size + 1;
	T* container = new T[size];

	for (size_t i = 0; i < size - 1; i++) {
		container[i] = data[i];
	}

	container[size-1] = elem;
	delete[] data;
	
	data = container;

	return size;

}
*/

template<class T>
inline size_t vec<T>::pop() {
	
	size = size - 1;
	T* container = new T[size];

	for (size_t i = 0; i < size; i++) {
		container[i] = data[i];
	}
	data = container;

	return size;

}


#endif	//POD_VECTOR == 0