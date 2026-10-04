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
	vec<long long int> a{ 1 }, b{ 1, 2 }, c{ 1, 2, 3 }, r;

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
			else {
				static bool add = 0;
				if (!add) std::cout << "addition failures\n";
				add++;
				fails++;
			}

			c = a - b;
			if (c[0] == i - j && c[1] == j - i) passes++;
			else {
				static bool sub = 0;
				if (!sub) std::cout << "Subtraction failures\n";
				sub++;
				fails++;
			}

			c = a * b;
			if (c[0] == i * j && c[1] == j * i) passes++;
			else {
				static bool mul = 0;
				if (!mul) std::cout << "Multiplication failures\n";
				mul++;
				fails++;
			}

			a = -c;
			if (a[0] == -c[0] && a[1] == -c[1]) passes++;
			else {
				static bool inv = 0;
				if (!inv) std::cout << "Inversion failures\n";
				inv++;
				fails++;
			}
			//a = {-i, 2*j+1};
			c.append(18);

			/*
			std::cout << c.length() << " - ";
			std::cout << std::sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]);
			std::cout <<" = " << std::abs(c.length() - std::sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2]))<<'\n';
			*/

			assert(std::abs(a.length() - std::sqrt(a[0] * a[0] + a[1] * a[1])) < 0.000001);
			assert(std::abs(b.length() - std::sqrt(b[0] * b[0] + b[1] * b[1])) < 0.000001);
			assert(std::abs(c.length() - std::sqrt(c[0] * c[0] + c[1] * c[1] + c[2] * c[2])) < 0.000001);
			if (a[0] == -c[0] && a[1] == -c[1]) passes++;
			else fails++;

			tests+=5;
		}
	}

	auto runtime = t.tick();

	std::cout << '\n';
	std::cout << tests << " tests executed. " << '\n' << passes << " passed" << '\n' << fails << " failed\n";
	std::cout << runtime << "s elapsed" << '\n' << (tests / runtime) / 1000000 << "Mln tests/sec\n\n";

	return 0;

}