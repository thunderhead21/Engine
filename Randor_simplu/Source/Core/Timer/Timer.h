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

	//number of seconds
	float tick()
	{


		end = clock.now();
		float dt = std::chrono::duration<float>(end - start).count();	//Default for duration is seconds

		start = end;

		return dt;
	}

	inline float elapsed() const { return std::chrono::duration<float>(clock.now() - start).count(); }

	void reset() { end = start = clock.now(); }
};

