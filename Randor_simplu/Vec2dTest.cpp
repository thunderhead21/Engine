#include "UTests.h"

bool TEST_vec2d_length() {
	auto start = Timer::now();
	std::cout << "Testing vec2d magnitude..." << std::endl;

	int tests = 0, fails = 0, passes = 0;
	//std::vector<vec2d> vec;

	for (int i = -10; i < 10; i++) {
		for (int j = -10; j < 10; j++) {
			
			tests++;

			auto v = vec2d((i % 2 ? i : -2 * i), (j % 2 ? j : -2 * j));
			//vec.push_back(v);

			float ref = sqrtf( (v.x * v.x) + (v.y * v.y));
			float mag = v.magnitude();
			float len = length(v);
			bool success = std::fabs(ref - mag) < EPS && std::fabs(ref - len) < EPS;
			if (!QUIET || !success) {
				std::cout<< std::boolalpha << std::setprecision(7) << "(" << v.x<<" , " << v.y << ")\t Magnitude: "<<ref<<"\t Consensus: " << success << std::endl;
			}

			if (success) passes++;
			else fails++;

			assert(std::fabs(ref - mag) < EPS && std::fabs(ref - len) < EPS);

		}
	}
	auto end = Timer::now();
	auto runtime = std::chrono::duration<double>(end - start);

	std::cout << tests << " tests executed. " << '\n' << passes << " passed" << '\n' << fails << " failed\n";
	std::cout << runtime.count() << "s elapsed"<<'\n' << (tests / runtime.count())/1000000 << "Mln tests/sec\n\n";

	return fails > 0 ? 1 : 0;;
}

bool TEST_vec2d_square() {
	auto start = Timer::now();
	std::cout << "Testing vec2d magnitude_square()..." << std::endl;

	int tests = 0, fails = 0, passes = 0;
	//std::vector<vec2d> vec;

	for (int i = -10; i < 10; i++) {
		for (int j = -10; j < 10; j++) {

			tests++;

			auto v = vec2d((i % 2 ? i : -2 * i), (j % 2 ? j : -2 * j));
			//vec.push_back(v);

			float ref = (v.x * v.x) + (v.y * v.y);
			float mag_sq = v.magnitude_square();
			float len = length_squared(v);
			bool success = std::fabs(ref - mag_sq) < EPS && std::fabs(ref - len) < EPS;
			if (!QUIET || !success) {
				std::cout << std::boolalpha << std::setprecision(7) << "(" << v.x << " , " << v.y << ")\t Magnitude: " << ref << "\t Consensus: " << success << std::endl;
			}

			if (success) passes++;
			else fails++;

			assert(std::fabs(ref - mag_sq) < EPS && std::fabs(ref - len) < EPS);

		}
	}
	auto end = Timer::now();
	auto runtime = std::chrono::duration<double>(end - start);

	std::cout << tests << " tests executed. " << '\n' << passes << " passed" << '\n' << fails << " failed\n";
	std::cout << runtime.count() << "s elapsed" << '\n' << (tests / runtime.count()) / 1000000 << "Mln tests/sec\n\n";

	return fails > 0 ? 1 : 0;;
}


bool TEST_vec2d_vertex() {
	auto start = Timer::now();
	std::cout << "Testing vec2d vertex()..." << std::endl;

	int tests = 0, fails = 0, passes = 0;
	//std::vector<vec2d> vec;

	for (int i = -10; i < 10; i++) {
		for (int j = -10; j < 10; j++) {

			tests++;

			auto v = vec2d((i % 2 ? i : -2 * i), (j % 2 ? j : -2 * j));
			auto vertex = v.vertex();

			bool success = std::fabs(v.x - vertex.position.x) < EPS && std::fabs(v.y - vertex.position.y) < EPS;
			if (!QUIET || !success) {
				std::cout << std::boolalpha << std::setprecision(7) << "(" << v.x << " , " << v.y << ")\t" << "\t Consensus: " << success << std::endl;
			}

			if (success) passes++;
			else fails++;

			assert(std::fabs(v.x - vertex.position.x) < EPS && std::fabs(v.y - vertex.position.y) < EPS);

		}
	}
	auto end = Timer::now();
	auto runtime = std::chrono::duration<double>(end - start);

	std::cout << tests << " tests executed. " << '\n' << passes << " passed" << '\n' << fails << " failed\n";
	std::cout << runtime.count() << "s elapsed" << '\n' << (tests / runtime.count()) / 1000000 << "Mln tests/sec\n\n";

	return fails > 0 ? 1 : 0;
}