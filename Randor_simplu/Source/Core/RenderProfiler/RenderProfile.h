#pragma once

#include "Core/Global/Macros.h"
/// @brief Provides per-frame timing breakdown. DESTROY - MOVE TO FRAMESTAT!
class RenderProfiler {
private:
	friend class Window;

	long double _frame{ 0L };

#if DETAILED_FRAME_PROFILER

	long double _event{ 0L };
	long double _clear{ 0L };
	long double _render_tform{ 0L };
	long double _projection{ 0L };
	long double _rendering{ 0L };
	long double _draw{ 0L };
	long double _presentation{ 0L };

#else
	long double _event{ -1L };
	long double _clear{ -1L };
	long double _render_tform{ -1L };
	long double _projection{ -1L };
	long double _rendering{ -1L };
	long double _draw{ -1L };
	long double _presentation{ -1L };

#endif	//DETAILED_FRAME_PROFILER

public:

	void frame_time(double frame) { _frame = frame; };
	void event_time(double event) { _event = event; };
	void clear_time(double clear) { _clear = clear; };
	void render_tform_time(double transform) { _render_tform = transform; };
	void projection_time(double projection) { _projection = projection; };
	void render_time(double rendering) { _rendering = rendering; };
	void draw_time(double draw) { _draw = draw; };
	void present_time(double presentation) { _presentation = presentation; };

	void print();

};