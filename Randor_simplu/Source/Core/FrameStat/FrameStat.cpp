#include "FrameStat.h"

void FrameStat::add(float dt)
{
	frames++;
	time_accumulator += dt;

	maximum = (dt > maximum) ? dt : maximum;
	minimum = (dt < minimum) ? dt : minimum;

	last_frame_time = dt;
}

long double FrameStat::accuracy() const
{
	return fabs((draw_time() + (_clear + _event + _presentation) / frames ) - mean_time());
}

std::string FrameStat::build_type() const
{
#ifdef _DEBUG
	return "DEBUG";
#elif  NDEBUG
	return "RELEASE";
#endif
}


#include <Windows.h>
#include <Psapi.h>

/// @brief Gets the current ram usage
/// @return Size_t MBs of ram used
std::size_t FrameStat::ram_usage() const	
{
	PROCESS_MEMORY_COUNTERS_EX pmc{};

	if (GetProcessMemoryInfo(
		GetCurrentProcess(),
		reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc),
		sizeof(pmc)))
	{
		return pmc.WorkingSetSize / (1024 * 1024);
	}

	return 0;
}
///Prints the values. Transforms them from seconds to milliseconds
void FrameStat::print() const
{
	std::cout << std::fixed << std::setprecision(10);
	std::cout << "\n\n============= STATISTICS =============" << std::endl;
	std::cout << "Average FPS:         " << average_fps() << '\n';
	std::cout << "Average Frame:       " << mean_time() * 1000ULL<< "ms" << "\n\n";

	std::cout << "Best:                " << min_time() * 1000ULL << "ms" <<'\n';
	std::cout << "Worst:               " << max_time() * 1000ULL << "ms" <<'\n';
	std::cout << "Frames:              " << frames <<"\n\n";
#if FRAME_PROFILER

	std::cout << "Event:               " << event_time() * 1000ULL << "ms" <<'\n';
	std::cout << "Screen clear:        " << clear_time() * 1000ULL << "ms" <<'\n';
	std::cout << "Draw:                " << draw_time() * 1000ULL << "ms\n";
	std::cout << "|->Render TForm:     " << render_tform_time() * 1000ULL << "ms" << '\n';
	std::cout << "|->Projection:       " << projection_time() * 1000ULL << "ms" <<'\n';
	std::cout << "L->Render:           " << render_time() * 1000ULL << "ms" <<'\n';
	std::cout << "Present:             " << present_time() * 1000ULL << "ms\n";
	std::cout << "deltaT (error):      " << accuracy() << "ms\n\n";
#endif
	std::cout << "Runtime:             " << runtime()<<"s\n\n";

	std::cout << "Build:               " << build_type() << '\n';
	std::cout << "RAM:                 " << ram_usage()<<"MB" << '\n';
	std::cout <<     "======================================" << "\n\n";


}

std::string FrameStat::str() const
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(10);
	ss << "\n\n============= STATISTICS =============" << std::endl;
	ss << "Average FPS:         " << average_fps() << '\n';
	ss << "Average Frame:       " << mean_time() * 1000ULL << "ms" << "\n\n";

	ss << "Best:                " << min_time() * 1000ULL << "ms" << '\n';
	ss << "Worst:               " << max_time() * 1000ULL << "ms" << '\n';
	ss << "Frames:              " << frames << "\n\n";
#if FRAME_PROFILER
	if (accuracy() > 1)		ss << "WARNING! DELTA-T ERROR IS GREATER THAN 1ms!\n";
	if (accuracy() > 10)	ss << "CRITICAL! MEASUREMENTS ARE UNRELIABLE!\n";
	ss << "Event:               " << event_time() * 1000ULL << "ms" << '\n';
	ss << "Screen clear:        " << clear_time() * 1000ULL << "ms" << '\n';
	ss << "Draw:               " << draw_time() * 1000ULL << "ms\n";
	ss << "|->Render TForm:     " << render_tform_time() * 1000ULL << "ms" << '\n';
	ss << "|->Projection:       " << projection_time() * 1000ULL << "ms" << '\n';
	ss << "L->Render:           " << render_time() * 1000ULL << "ms" << '\n';
	ss << "Present:             " << present_time() * 1000ULL << "ms\n";
	ss << "deltaT (error):      " << accuracy() << "ms\n\n";
#endif
	ss << "Runtime:             " << runtime() << "s\n\n";

	ss << "Build:               " << build_type() << '\n';
	ss << "RAM:                 " << ram_usage() << "MB" << '\n';
	ss << "======================================" << "\n\n";


	return ss.str();
}
