#pragma once

#include <math.h>
#include <iostream>
#include "Vector.h"
#include "Core.h"

/// @brief Column-major order. Solves to array. Transforms vertices.
/// @brief Column-major means as you progress, you advance through the columns, then lines
namespace internal {
	static vec4d v4;
}

template <typename T = float>
class  mat {
protected:
	const size_t columns, rows, size;
	const bool is_square;
	T* data;


	void copyDataFrom(const mat<T>& other) {
		if (rows != other.rows || columns != other.columns)
			throw std::invalid_argument("Size mismatch");
		std::copy(other.data, other.data + size, data);
	}

public:
	//Constructors
	mat(size_t rows = 4, size_t columns = 0);
	mat(const mat<T>& other);

	//Destructor
	~mat();

	//Builds and return matrices
	static mat<T> identity();		///Return Identity matrix (1 on main diagonal)

	inline static mat<T> translation(T x, T y, T z);	///Return translation matrix
	static mat<T> translation(const vec3d& v);	///Return translation matrix from vector
	static mat<T> translation(const vec4d& v);	///Return translation matrix from vector. Discards W.

	static mat<T> rotation_x(T degs);	///Return rotation matrix around X axis
	static mat<T> rotation_y(T degs);	///Return rotation matrix around Y axis
	static mat<T> rotation_z(T degs);	///Return rotation matrix around Z axis
	static mat<T> rotation(T x_degs, T y_degs, T z_degs);		///Return rotation matrix around X Y Z axis

	static mat<T> rotation(const vec3d& v);		///Return rotation matrix around X Y Z axis
	static mat<T> rotation(const vec4d& v);		///Return rotation matrix around X Y Z axis

	static mat<T> scale(T uniform);		///Return scale matrix (1 * axis_scale on main diagonal)
	static mat<T> scale(const vec3d& v);		///Return scale matrix (1 * axis_scale on main diagonal)
	static mat<T> scale(const vec4d& v);		///Return scale matrix (1 * axis_scale on main diagonal)
	static mat<T> scale(T x, T y, T z);		///Return scale matrix (1 * axis_scale on main diagonal)

	mat<T> perspective();	///Returns perspective projection matrix
	mat<T> ortographic();	
	mat<T> look_at();		
	mat<T> transpose();	///Inverts the columns and rows
	mat<T> inverse();		///Returns the inverse matrix, where A * inverse(A) = Identity
	mat<T> trs();			///Returns the matrix that applies the given translation, rotation and scaling

	T& operator[](size_t index);			//Return a value from the underlying array.
	const T& operator[](size_t index) const ;

	//Assignment operator
	mat<T>& operator=(const mat& other);

	//Equality operator
	bool operator==(const mat& other) const;

	//OPERATOR* NEVER changes the matrix, it returns a new one.
	//OPERATOR*= does that
	vec4d operator*(const vec4d& v)  ;	//Mat * Vec operator
	vec4d operator*(const vec3d& v) ;	//Mat * Vec operator
	mat<T> operator*(const mat<T>& other) ;	//Mat * Mat operator


	//Matrix Accessors
	T& operator()(size_t row, size_t column);
	const T& operator()(size_t row, size_t column) const;

	T& at(size_t row, size_t column);
	const T& at(size_t row, size_t column) const;
	
	size_t num_columns() const { return columns; }
	size_t num_rows()	 const { return rows; }
	size_t num_size()	 const { return size; }
	const T* get_data()	 const { return data; }

	void print(); 
};

template <class T = float>
class mat2_t : public mat<T> {
public:
	mat2_t() : mat<T>(2, 2) {} // Calls base constructor with fixed size
	mat2_t(const mat<T>& other) : mat<T>(2, 2) {
		if (other.num_rows() != 2 || other.num_columns() != 2)
			throw std::invalid_argument("Size mismatch");
		std::copy(other.get_data(), other.get_data() + 4, this->data);
	}

	mat2_t<T> scale(int x);

};


template <class T = float>
class mat3_t : public mat<T> {
public:
	mat3_t() : mat<T>(3, 3) {};
	mat3_t(const mat<T>& other) : mat<T>(3, 3) {
		if (other.num_rows() != 3 || other.num_columns() != 3)
			throw std::invalid_argument("Size mismatch");
		std::copy(other.get_data(), other.get_data() + 9, this->data);
	}
};

template <class T = float>
class mat4_t : public mat<T> {
public:
	inline mat4_t() : mat<T>(4, 4) {};
	inline mat4_t(const mat<T>& other) : mat<T>(4, 4) {
		if (other.num_rows() != 4 || other.num_columns() != 4)	throw std::invalid_argument("Size mismatch");
		std::copy(other.get_data(), other.get_data() + 16, this->data);
	}
};

////////FLOAT MATRICES////////

typedef mat2_t<float> mat2;
typedef mat3_t<float> mat3;
typedef mat4_t<float> mat4;
//typedef mat4 mat;

////////DOUBLE MATRICES////////
typedef mat2_t<double> dmat2;
typedef mat3_t<double> dmat3;
typedef mat4_t<double> dmat4;

#include "Matrix.inl"
