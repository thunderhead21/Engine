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

Mesh& Window::load_entity_mesh(Entity& ent) {

	throw "load_entity_mesh() called. UNUSED!";

	///Temporarily unused. Does the window care about entities or just meshes?
	/// 
	///meshes.push_back(ent.get_Mesh());
	///return meshes.at(meshes.size()-1);

}	//Only cares about the Mesh component of the entity

Entity* Window::enroll_entity(Entity& ent)
{
	entities.push_back(&ent);
	return entities.at(entities.size() - 1);
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

	register_own_keybindings();
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

		case SDL_EVENT_KEY_DOWN:	// Process key presses. Since that was off-loaded, do nothing

			break;

		case SDL_EVENT_WINDOW_RESIZED:
		{
			int x, y;
			SDL_GetCurrentRenderOutputSize(renderer, &x, &y);
			w = x, h = y;
			spdlog::info("RESIZED: W - {} H - {}", w, h);

			break;
		}
		case SDL_EVENT_MOUSE_BUTTON_DOWN: // Process mouse input
			float x, y;
			mouse = SDL_GetMouseState(&x, &y);	//Get position of the mouse

			/*	Limbo state. Not used while simply working on redering
			if (mouse & LMB) {
				//SDL_GetMouseState(&a, &b);
				pts.push_back({ x, y });

				if (INFO) spdlog::info("LMB DOWN at X:{}, Y:{}", x, y);

			}
			else if (mouse & RMB) {
				tmp->x = x;
				tmp->y = y;
				if (INFO) spdlog::info("RMB DOWN at X:{}, Y:{}", x, y);
			}
			*/

			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			/*	Limbo state. Not used while simply working on redering 
			SDL_GetMouseState(&x, &y);
			if (mouse & RMB) {
				if (INFO) spdlog::info("RMB UP at X:{}, Y:{}", x, y);
				//tmp->w = fabs(x - tmp->x);
				//tmp->h = fabs(y - tmp->y);
				tmp->w = (x - tmp->x);
				tmp->h = (y - tmp->y);

			}
			*/
			break;
		}
	}
}

void Window::update(){
	
	//handle_events();

	// Clear screen with a nice color
	SDL_SetRenderDrawColor(renderer, 20, 25, 35, 255);
	SDL_RenderClear(renderer);
		
	////////////////// Draw something simple (a rectangle)
	shader();
	//////////////////

	// Present the frame
	SDL_RenderPresent(renderer);
		
	
}

Window::~Window() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}