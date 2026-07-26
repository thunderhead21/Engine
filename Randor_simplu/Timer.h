#pragma once

#include <chrono>

class Timer
{
private:
	std::chrono::steady_clock clock;

	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;

public:
	Timer();

	//number of milliseconds
	float tick()
	{


		end = clock.now();
		std::chrono::milliseconds dt = std::chrono::duration_cast<std::chrono::milliseconds>((end - start));

		start = clock.now();

		return dt.count()/1000.0f;
	}
};

