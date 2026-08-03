#include "FrameStat.h"

void FrameStat::add(float dt)
{
	frames++;
	time_accumulator += dt;

	maximum = (dt > maximum) ? dt : maximum;
	minimum = (dt < minimum) ? dt : minimum;
}

void FrameStat::print() const
{
	std::cout << std::fixed << std::setprecision(10);
	std::cout << "\n\n=========== STATISTICS ===========" << std::endl;
	std::cout << "Average FPS:      " << average_fps() << '\n';
	std::cout << "Average Frame:    " << mean_time() * 1000ULL<< "ms" << "\n\n";
	std::cout << "Best:             " << min_time() * 1000ULL << "ms" <<'\n';
	std::cout << "Worst:            " << max_time() * 1000ULL << "ms" <<'\n';
	std::cout << "Frames:           " << frames <<'\n';
	std::cout << "Runtime:          " << runtime()<<'s' << '\n';
	std::cout <<     "==================================" << "\n\n";


}
