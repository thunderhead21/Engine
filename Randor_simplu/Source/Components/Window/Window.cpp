#include "Window.h"

bool Window::init_attempted = 0;
bool Window::init_success = 0;


bool Window::init() {
	{
		if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
			SDL_Log("SDL_Init failed: %s", SDL_GetError());
			if (DEBUG) throw "SDL_Init failed";
			return 1;
		}
		else return 0;
	}
}

/// REMEMBER! ALL keybindings must be of void return value
void Window::register_own_keybindings()
{
	controller.register_keybind(SDL_SCANCODE_ESCAPE, [&] {valid = 0; });	//Quit by pressing ESC
}

int Window::set_fps(unsigned int fps) noexcept
{
	this->fps = fps;
	if (fps > 0) target_frame_time_s = 1.0f / fps;
	return fps;
}



bool Window::set_active_scene(Scene& s)
{
	scene = &s;
	s.rebuild_queues();
	return s.empty();
}

Window::Window(InputManager& controller, int w, int h, bool VSync, bool fullscreen):
	window(nullptr), renderer(nullptr), w(w), h(h), vsync(VSync), mouse(0), aspect_ratio(w / h), event({}), valid(1), controller(controller)
{
	if (init_attempted == 0) {
		init_success = !init();
		init_attempted = 1;
	}

	SDL_WindowFlags options = SDL_WINDOW_RESIZABLE | (fullscreen * SDL_WINDOW_FULLSCREEN);

	if (!SDL_CreateWindowAndRenderer("SDL3 Boilerplate", w, h, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		SDL_Log("Failed to create window/renderer: %s", SDL_GetError());
		SDL_Quit();
		if (DEBUG) throw "Failed to create window / renderer:" + (std::string)SDL_GetError();
	}
	
	if (!SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND)) {
		SDL_Log("Failed to set blending mode: %s", SDL_GetError());
	};

	if (VSync) {
		SDL_SetRenderVSync(renderer, 1);  // Enable vsync
		fps = 75;
	}
	else {
		SDL_SetRenderVSync(renderer, 0);  // Disable vsync
		fps = 0;
	}

	if (fps > 0) target_frame_time_s = 1.0f / fps;

	register_own_keybindings();

	timer.reset();	//Prime the timer, discard the startup time.... or not!
}

//Keep only internals here. Delegate controls
void Window::handle_events() {	// Window related event handling



	//Be VERY cautious of duplicate events
	/*	OBSOLETE! TRANSITION TO InputManager! by providing appropriate function pointers
	*	FALSE - Input Manager has no authority over a Window's events.
	* Therefore, processing those locally is mandatory
	*/

	while (SDL_PollEvent(&event)) {

		switch (event.type) {
		case SDL_EVENT_QUIT:
			valid = 0;
			spdlog::warn("X pressed. Quitting.");

			break;

		case SDL_EVENT_WINDOW_RESIZED:
		{
			int x, y;
			SDL_GetCurrentRenderOutputSize(renderer, &x, &y);
			w = x, h = y;
			spdlog::info("RESIZED: W - {} H - {}", w, h);

			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_DOWN: // Process mouse input -- MOVE TO THE InputManager!
			float x, y;
			mouse = SDL_GetMouseState(&x, &y);	//Get position of the mouse

		default:

			break;
		}
	}
}




#if FRAME_PROFILER
Timer instrument;
#endif // FRAME_PROFILER

float Window::update(){
#if FRAME_PROFILER
	instrument.reset();
#endif // FRAME_PROFILER

	handle_events();

#if FRAME_PROFILER
	spdlog::info( "Event Handling: {} ms", instrument.tick() * 1000);
	instrument.reset();
#endif

	// Clear screen with a nice color
	SDL_SetRenderDrawColor(renderer, 20, 25, 35, 255);
	SDL_RenderClear(renderer);
#if FRAME_PROFILER
	spdlog::info("Screen clear: {} ms", instrument.tick() * 1000);
	instrument.reset();
#endif

	////////////////// Draw something simple (a rectangle)
	shader();
	//////////////////
#if FRAME_PROFILER
	spdlog::info("Draw: {} ms", instrument.tick() * 1000);
	instrument.reset();
#endif // FRAME_PROFILER


	// Present the frame
	SDL_RenderPresent(renderer);
#if FRAME_PROFILER
	spdlog::info("Presentation: {} ms\n\n", instrument.tick() * 1000);
#endif // FRAME_PROFILER

#if FRAME_PACER	//If the frame pacer was enabled
		
	float elapsed = timer.elapsed();
		
	// Wait as long as the framerate requires
	do{
		elapsed = timer.elapsed() ;
	} while (elapsed < target_frame_time_s);

	timer.reset();
	

#elif !FRAME_PACER	//If framepacer is disabled

	float elapsed = timer.elapsed();
	timer.reset();

#endif
	return elapsed;
}

Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}