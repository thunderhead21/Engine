#include "UTests.h"


void TEST_platform_scheduler_precision(unsigned int duration, unsigned int iterations){

	Timer t;

	std::vector<float> times;
	std::set<float> unique;

	t.tick();
	for (int i = 0; i < iterations; i++) {

		SDL_Delay(duration);
		float laptime = t.tick();
		times.push_back(laptime);
		unique.insert(laptime);
	}

	std::cout << std::setprecision(10);
	std::cout << "Requested delay: " <<duration << '\n';
	std::cout << "Requested iterations: " << iterations << '\n';

	unsigned int count = 0;

	for (auto& i : unique) {

		for (auto& j : times) {
			if (i == j) count++;
		}

		std::cout << i << " appears " << count << " times " << "("<<((float)count/times.size())*100.0f<<"%)" << '\n';
		count = 0;
	}
}