#include "Matrix.hpp"


/////////////////// CONSTRUCTORS ///////////////////

template<typename T>
inline mat<T>::mat(size_t rows, size_t columns):
	rows(rows), 
	columns(columns == 0 ? rows : columns), 
	size(rows * (columns == 0 ? rows : columns)), 
	is_square(rows == (columns == 0 ? rows : columns)),
	data( new T[size]())
{ 
	if(this->rows == 0 || this->columns == 0) throw std::invalid_argument("Matrix dimensions cannot be zero");
}

template<typename T>
inline mat<T>::mat(const mat<T>& other):
	rows(other.rows), columns(other.columns), data(new T[other.size]), size(other.size), is_square(rows == (columns == 0 ? rows : columns))
{
	copyDataFrom(other);
}

//////////////////// DESTRUCTORS ////////////////////
template<typename T>
inline mat<T>::~mat()
{
	delete[] data;
}

/////////////////// OPERATORS ///////////////////
template <typename T>
inline T& mat<T>::operator[](size_t index) { 
	if (index >= size ) throw std::out_of_range("Invalid index requested");
	
	return data[index];
}

template <typename T>
inline const T& mat<T>::operator[](size_t index) const {
	if (index >= size) throw std::out_of_range("Invalid index requested");

	return data[index];
}

template<typename T>
inline mat<T>& mat<T>::operator=(const mat& other)
{
	if (this == &other) return *this;
	else if (rows != other.rows || columns != other.columns) throw "Matrices have to be of equal size to assign";

	copyDataFrom(other);

	return *this;
}

template<typename T>
inline bool mat<T>::operator==(const mat& other) const 
{
	//If one of the dimensions is different, the matrices are NOT equal
	if(size != other.size || rows != other.rows || columns != other.columns) return false;
	
	//However, if the dimensions and each element is equal, they are equal
	for (size_t i = 0; i < size; i++) {

		//So we check each position to see if the elements are equal.
		//Once two elements differ from eachother, they are no longer equal
		if (data[i] != other[i]) return false;

	}
	
	//If we got to this point, the two certainly are equal
	return true;
}

template<typename T>
inline vec4d mat<T>::operator*(const vec4d& v) const
{
	vec4d result{0,0,0,0};
	for (int i = 0; i < rows; i++) {
		
		result[i] = (v[0] * at(i, 0)) + (v[1] * at(i, 1)) + (v[2] * at(i, 2)) + (v[3] * at(i, 3));
		//result[i] = (v[i] * at(0, i)) + (v[i] * at(1, i)) + (v[i] * at(2, i)) + (v[i] * at(3, i));
		
	}
	return result;
}

template<typename T>
inline vec4d mat<T>::operator*(const vec3d& v) const
{
	
	vec4d result{ v.x, v.y, v.z, 1 };
	//std::cout<< "START: " << result << std::endl;
	for (int i = 0; i < rows; i++) {

		result[i] = (v[0] * at(i, 0)) + (v[1] * at(i, 1)) + (v[2] * at(i, 2)) + (1 * at(i, 3));

	}
	//std::cout <<"END:" << result << std::endl;
	return result;
}

template<typename T>
inline mat<T> mat<T>::operator*(const mat<T>& other) const
{
	assert(columns == other.rows);

	if (columns != other.rows) throw std::invalid_argument("Incompatible matrix dimensions");

	mat<T> result(rows, other.columns);
	//	IF square matrix with side of 4
	if( is_square && columns == 4 ) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < other.columns; j++) {
				
				///eliminated this->at(...)
				result.at(i, j) = this->at(i, 0) * other.at(0, j) + this->at(i, 1) * other.at(1, j) + this->at(i, 2) * other.at(2, j) + this->at(i, 3) * other.at(3, j);


			}
		}
	}
	else if (is_square && columns == 3) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < other.columns; j++) {

				result.at(i, j) = this->at(i, 0) * other.at(0, j) + this->at(i, 1) * other.at(1, j) + this->at(i, 2) * other.at(2, j);


			}
		}
	}
	else if (is_square && columns == 2) {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < other.columns; j++) {

				result.at(i, j) = this->at(i, 0) * other.at(0, j) + this->at(i, 1) * other.at(1, j) ;


			}
		}
	}

	else {
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < other.columns; j++) {
				for(size_t k = 0; k < columns; k++)
				result.at(i, j) += this->at(i, k) * other.at(k, j);


			}
		}
	}

	return result;
}

/*
template<typename T>
inline mat<T> mat<T>::operator*(mat<T>& other) const
{
	mat<T> result;

	if constexpr ( == 4) {
		for (size_t i = 0; i < ; i++) {
			for (size_t j = 0; j < ; j++) {

				///eliminated this->at(...)
				result.at(i, j) = this->at(i, 0) * other.at(0, j) + this->at(i, 1) * other.at(1, j) + this->at(i, 2) * other.at(2, j) + this->at(i, 3) * other.at(3, j);


			}
		}
	}
	else if ( == 3) {
		for (size_t i = 0; i < ; i++) {
			for (size_t j = 0; j < ; j++) {

				result.at(i, j) = this->at(i, 0) * other.at(0, j) + this->at(i, 1) * other.at(1, j) + this->at(i, 2) * other.at(2, j);


			}
		}
	}
	else if ( == 2) {
		for (size_t i = 0; i < ; i++) {
			for (size_t j = 0; j < ; j++) {

				result.at(i, j) = this->at(i, 0) * other.at(0, j) + this->at(i, 1) * other.at(1, j);


			}
		}
	}

	else {
		for (size_t i = 0; i < ; i++) {
			for (size_t j = 0; j < ; j++) {
				for (size_t k = 0; k < ; i++)
					result.at(i, j) += this->at(i, k) * other.at(k, j);


			}
		}
	}

	return result;
}
*/


template<typename T>
inline T& mat<T>::operator()(size_t row, size_t column)
{
	return data[column *  + row];
}

template<typename T>
inline const T& mat<T>::operator()(size_t row, size_t column) const
{
	return data[column *  + row];
}

template<typename T>
inline T& mat<T>::at(size_t row, size_t column)
{
	return data[column * rows + row];
}

template<typename T>
inline const T& mat<T>::at(size_t row, size_t column) const
{
	return data[column * rows + row];
}

template<typename T>
inline void mat<T>::print()
{
	for (size_t row = 0; row < rows; ++row)	//For each row
	{
		for (size_t col = 0; col < columns; ++col)	//Print each column
			std::cout << at(row, col) << ' ';

		std::cout << '\n';
	}
}

/////////////////// FACTORIES ///////////////////
template <typename T>
inline mat<T> mat<T>::identity()
{
	mat<T> id;
	
	if (id.is_square == 0) throw "identity is not square";

	for (size_t i = 0; i < id.size; i += id.columns + 1) {
		
		id[i] = T(1);

	}
	return id;
}

template<typename T>
inline mat<T> mat<T>::translation(T x, T y, T z)
{
	mat<T> trans = identity();
	if (!trans.is_square) throw "Identity matrix is not square";

	/*	This places the translaton ammount at the bottom of the matrix, Direct 3D style
	if (( * 1 - 1) <  * ) trans.data[ * 1 - 1] = x;
	if (( * 2 - 1) <  * ) trans.data[ * 2 - 1] = y;
	if (( * 3 - 1) <  * ) trans.data[ * 3 - 1] = z;
	*/

	///Later - Handle requested translation matrix for size < mat4 gracefully
	size_t end = trans.rows * trans.columns;
	if (end - 4 >= 0) {
		trans.data[end - 4] = x;
		trans.data[end - 3] = y;
		trans.data[end - 2] = z;
	}

	return trans;
}

template<typename T>
inline mat<T> mat<T>::translation(const vec3d& v)
{
	mat<T> trans = identity();
	size_t end =  trans.size ;
	
	trans.data[end - 4] = v.x;
	trans.data[end - 3] = v.y;
	trans.data[end - 2] = v.z;
	

	return trans;
}

template<typename T>
inline mat<T> mat<T>::translation(const vec4d& v)
{
	mat<T> trans = identity();
	size_t end = trans.size;

	trans.data[end - 4] = v.x;
	trans.data[end - 3] = v.y;
	trans.data[end - 2] = v.z;
	return trans;
}

template<typename T>
inline mat<T> mat<T>::rotation_x(T degs)
{
	const T rads = radians(degs);

	const T c = std::cos(rads);
	const T s = std::sin(rads);

	mat<T> rot = identity();

	rot.at(1, 1) = c;
	rot.at(2, 2) = c;
	rot.at(1, 2) = -s;
	rot.at(2, 1) = s;

	return rot;
}

template<typename T>
inline mat<T> mat<T>::rotation_y(T degs)
{
	const T rads = radians(degs);

	const T c = std::cos(rads);
	const T s = std::sin(rads);

	mat<T> rot = identity();

	rot.at(0, 0) = c;
	rot.at(0, 2) = s;
	rot.at(2, 0) = -s;
	rot.at(2, 2) = c;

	return rot;
}

template<typename T>
inline mat<T> mat<T>::rotation_z(T degs)
{
	const T rads = radians(degs);

	const T c = std::cos(rads);
	const T s = std::sin(rads);

	mat<T> rot = identity();
	rot.at(0, 0) = c;
	rot.at(0, 1) = -s;
	rot.at(1, 0) = s;
	rot.at(1, 1) = c;
	return rot;
}

template<typename T>
inline mat<T> mat<T>::rotation(T x_degs, T y_degs, T z_degs)
{
	return (rotation_z(z_degs) * rotation_y(y_degs) * rotation_x(x_degs));
}

template<typename T>
inline mat<T> mat<T>::rotation(const vec3d& v)
{
	return rotation(v.x, v.y, v.z);
}

template<typename T>
inline mat<T> mat<T>::rotation(const vec4d& v)
{
	return rotation(v.x, v.y, v.z);
}

template<typename T>
inline mat<T> mat<T>::scale(T x, T y, T z)
{
	mat<T> scale = mat::identity();

	if (!scale.is_square) throw "identity matrix is not square";

	///Obtain the sequence you need and keep track of which you need
	T multiplier[3] = { x, y, z };
	size_t multiplier_index = 0;

	//Go through the main diagonal and apply until there is none left to aply
	for (size_t i = 0; i < scale.size; i += scale.columns + 1, multiplier_index++) {

		if (multiplier_index < 3) scale[i] = T(multiplier[multiplier_index]);
		else break;
	}

	return scale;
}

template<typename T>
inline mat<T> mat<T>::scale(T uniform)
{
	mat<T> scale = mat::identity();
	if (!scale.is_square) throw "identity matrix is not square";

	for (size_t i = 0; i < scale.size; i += scale.columns + 1) {

		scale[i] = T(uniform);
		if(i > scale.columns * 3)	break;
	}

	return scale;
}

template<typename T>
inline mat<T> mat<T>::scale(const vec3d& v) { return scale(v.x, v.y, v.z); };

template<typename T>
inline mat<T> mat<T>::scale(const vec4d& v) { return scale(v.x, v.y, v.z); };

