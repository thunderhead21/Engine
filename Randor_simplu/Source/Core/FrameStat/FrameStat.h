#pragma once

#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>

#include "Core/Global/Macros.h"

/*DO NOT INCLUDE THESE HERE

#include <Windows.h>
#include <Psapi.h>

long double minimum{ std::numeric_limits<long double>::max() };
													  ^~~~~~
												This will be in conflict with 
												a macro in the headers!	

Those were included in the .CPP
*/

//For general frame time analysis
class FrameStat
{
protected:

	unsigned long long frames{ 0 };
	long double time_accumulator{ 0.0L };

	//Being profiler values, memory cost is negligible for high precision
	long double minimum{ std::numeric_limits<long double>::max() };
	long double maximum{ 0.0L  };
	long double last_frame_time{ 0 };

#if FRAME_PROFILER
	///Accumulator variables in seconds.
	long double _event{ 0L };
	long double _clear{ 0L };
	long double _render_tform{ 0L };
	long double _projection{ 0L };
	long double _rendering{ 0L };
	long double _draw{ 0L };
	long double _presentation{ 0L };

	long double _phys{ 0L };

#else
	long double _event{ -1L };
	long double _clear{ -1L };
	long double _render_tform{ -1L };
	long double _projection{ -1L };
	long double _rendering{ -1L };
	long double _draw{ -1L };
	long double _presentation{ -1L };
	
	long double _phys{ -1L };

#endif	//DETAILED_FRAME_PROFILER


public:
	FrameStat() = default;
	~FrameStat() = default;

	void add(float dt);

	inline long double average_fps()	const { return time_accumulator > 0.0L ? (long double) frames / time_accumulator : 0; }
	inline long double mean_time()		const { return frames > 0ULL ? time_accumulator / (long double) frames : 0 ; }
	inline long double min_time()		const { return minimum; }
	inline long double max_time()		const { return maximum; }
	inline long double last()			const { return last_frame_time; }
	inline long double runtime()		const { return time_accumulator; }

	inline void event_time(long double event) { _event += event; };
	inline void clear_time(long double clear) { _clear += clear; };
	inline void render_tform_time(long double transform) { _render_tform += transform; };
	inline void projection_time(long double projection) { _projection += projection; };
	inline void render_time(long double rendering) { _rendering += rendering; };
	inline void draw_time(long double draw) { _draw += draw; };
	inline void present_time(long double presentation) { _presentation += presentation; };
	inline void physics_time(long double physics) { _phys += physics; }
	
	inline long double event_time() const { return _event / frames; };
	inline long double clear_time() const { return _clear / frames; };
	inline long double render_tform_time() const { return _render_tform / frames; };
	inline long double projection_time() const { return _projection / frames; };
	inline long double render_time() const { return _rendering / frames; };
	inline long double draw_time() const { if (_draw)return _draw / frames; else return (_render_tform + _projection + _rendering) / frames; };
	inline long double present_time() const { return _presentation / frames; };
	long double accuracy() const;

	/* ALTERNATIVE DEFINITION
	inline long double event_time() const { return _event ; };
	inline long double clear_time() const { return _clear ; };
	inline long double render_tform_time() const { return _render_tform ; };
	inline long double projection_time() const { return _projection ; };
	inline long double render_time() const { return _rendering ; };
	inline long double draw_time() const { return _draw ; };
	inline long double present_time() const { return _presentation ; };
	*/

	std::string build_type()	const;
	size_t ram_usage()			const;


	void print() const;
	std::string str() const;
};

