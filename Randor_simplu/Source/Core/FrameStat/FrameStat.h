#pragma once

#include <iostream>
#include <iomanip>
#include <limits>

class FrameStat
{
protected:

	unsigned long long frames{ 0 };
	long double time_accumulator{ 0.0L };

	//Being profiler values, memory cost is negligible for high precision
	long double minimum{ std::numeric_limits<long double>::max() };
	long double maximum{ 0.0L  };
	long double last_frame_time{ 0 };


public:
	FrameStat() = default;
	~FrameStat() = default;

	void add(float dt);

	long double average_fps()	const { return time_accumulator > 0.0L ? (long double) frames / time_accumulator : 0; }
	long double mean_time()		const { return frames > 0ULL ? time_accumulator / (long double) frames : 0 ; }
	long double min_time()		const { return minimum; }
	long double max_time()		const { return maximum; }
	long double last()			const { return last_frame_time; }
	long double runtime()		const { return time_accumulator; }

	void print() const;

};

