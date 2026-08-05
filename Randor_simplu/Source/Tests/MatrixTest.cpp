#include <iostream>
#include "../Components/Math/Matrix/Matrix.hpp"

bool TEST_matrix_identity(){

	for (size_t i = 2; i < 10; i++) {
		const size_t size = i;
		//mat<double, size> m;
	}

	return 1;
}

void TEST_matrix_creation(){

	////////////// IDENTITY TEST //////////////
	mat2 m2 = m2.identity();	//Identity has
	mat3 m3 = m3.identity();	//to exist for
	mat4 m4 = m4.identity();	//ALL matrices

	m2.print();
	std::cout << '\n';
	m3.print();
	std::cout << '\n';
	m4.print();
	std::cout << '\n';
	std::cout << '\n';

	////////////// UNI-SCALE TEST //////////////
	//m2 = m2.scale(3);	//M2 scale does not exist
	//m3 = m3.scale(3);	M3 scale is defined for 2D objects. Takes X, Y parameters
	m4 = m4.scale(3);
	m2.print();
	std::cout << '\n';
	m3.print();
	std::cout << '\n';
	m4.print();
	std::cout << '\n';
	std::cout << '\n';

	////////////// C-TOM SCALE TEST //////////////
	//m2 = m2.scale(3, 6, 9);	M2 scale does not exist
	//m3 = m3.scale(3, 6, 9);	M3 scale has X, Y components
	m4 = m4.scale(3, 6, 9);
	m2.print();
	std::cout << '\n';
	m3.print();
	std::cout << '\n';
	m4.print();
	std::cout << '\n';
	std::cout << '\n';

	/////////// C-TOM TRANSLATION TEST ///////////
	//m2 = m2.translation(3, 6, 9);	M2 translation does not exist
	//m3 = m3.translation(3, 6, 9);	M3 translation is relative to X and Y
	m4 = m4.translation(3, 6, 9);
	m2.print();
	std::cout << '\n';
	m3.print();
	std::cout << '\n';
	m4.print();
	std::cout << '\n';
	std::cout << '\n';
	/////////// C-TOM ROTATION TEST ///////////
	//m2 = m2.rotation_z(90);	M2 rotation CANNOT exist
	//m3 = m3.rotation_z(90);	M3 rotation is done around a point
	m4 = m4.rotation_z(90);
	m2.print();
	std::cout << '\n';
	m3.print();
	std::cout << '\n';
	m4.print();
	std::cout << '\n';
	std::cout << '\n';
	//////// MATRIX MULTIPLICATION TEST ////////
	m4 = mat4::translation(2, 3, 4);
	m4.print();
	vec4d v4 = m4 * vec4d(4, 3, 2, 1.25);
	//std::cout << ' * ' << v4 << std::endl;
	std::cout << '\n' << v4 << std::endl;

}

void TEST_matrix_rotation(){

	auto I = mat4::identity();
	std::cout << "IDENTITY:" << std::endl;
	(I * I).print();
	std::cout << std::endl;

	auto r1 = mat4::rotation_x(45);
	std::cout << "ROT_X:" << std::endl;
	r1.print();
	std::cout << std::endl;

	auto r2 = mat4::rotation_y(45);
	std::cout << "ROT_Y:" << std::endl;
	r2.print();
	std::cout << std::endl;

	auto r3 = mat4::rotation_z(45);
	std::cout << "ROT_Z:" << std::endl;
	r3.print();
	std::cout << std::endl;

	auto r4 = mat4::rotation({ 45, 0, 0 });

	std::cout << "ROTATION MATRIX:" << std::endl;
	(I * r1 * r2 * r3 * r4).print();
	std::cout << std::endl;

	vec3d x{ 1,0,0 };
	std::cout << "X ROT_X(90)" << mat4::rotation_z(90) * x << '\n';

	vec3d y{ 0,1,0 };
	std::cout << "Y X_ROT(90)" << mat4::rotation_x(90) * y << '\n';

	vec3d z{ 0,0,1 };
	std::cout << "Z ROT_Y(90)" << mat4::rotation_y(90) * z << '\n';
}
