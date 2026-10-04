#include "UTests.h"


bool TEST_tpt_vector_access_operator()
{

	vec<int> a{1,2,3,4};
	a[0] = 0;
	a[1] = 1;
	a[2] = 2;
	a[3] = 3;

	assert(a[0] == 0 && a[1] == 1 && a[2] == 2 && a[3] == 3);



	return 1;
}

bool TEST_tpt_vector_add()
{
	std::cout << "Testing vector<int> arithmetic..." << std::endl;
	vec<int> a{ 1 }, b{ 1, 2 }, c{ 1, 2, 3 }, r;

	auto ab = a + b;
	assert(ab[0] == 2 && ab[1] == 2);

	auto bc = b + c;
	assert(bc[0] == 2 && bc[1] == 4 && bc[2] == 3);

	auto ac = a + c;
	assert(ac[0] == 2 && ac[1] == 2 && ac[2] == 3);

	auto abc = a + b + c;
	assert(abc[0] == 3 && abc[1] == 4 && abc[2] == 3);


	Timer t;
	size_t tests = 0, fails = 0, passes = 0;
	for (int i = -1000; i < 2000; i++) {
		for (int j = -2000; j < 1000; j++) {
			a = { i, j };
			b = { j, i };

			c = a + b;
			if(c[0] == i + j && c[1] == i + j) passes++;
			else fails++;

			c = a - b;
			if (c[0] == i - j && c[1] == j - i) passes++;
			else fails++;

			c = a * b;
			if (c[0] == i * j && c[1] == j * i) passes++;
			else fails++;



			tests+=3;
		}
	}

	auto runtime = t.tick();

	std::cout << tests << " tests executed. " << '\n' << passes << " passed" << '\n' << fails << " failed\n";
	std::cout << runtime << "s elapsed" << '\n' << (tests / runtime) / 1000000 << "Mln tests/sec\n\n";

	return 0;

}