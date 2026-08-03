#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "../Scene/Scene.h"
#include "../Input/InputManager/InputManager.h"

#define FRAME_PACER 1		//Smooth busy-waiting for precise frame times
#define FRAME_PROFILER 0	//Print every render stage timing breakdown

constexpr bool DEBUG = 0;
constexpr bool INFO = 0;


class Entity;
struct vec3d;

class Window		//Needs to separate the renderer and window ASAP!
{

	//Future Vertex Buffer Object
	std::vector<vec4d> world_vertices;
	std::vector<SDL_Vertex> render_vertices;

	Timer timer;
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	SDL_MouseButtonFlags mouse;

	InputManager& controller;

	unsigned int w, h, fps;

	bool vsync;
	bool valid;
	static bool init_success, init_attempted;
	double aspect_ratio;
	double target_frame_time_s;

	bool init();
	void register_own_keybindings();

	//Prevent changing the scene
	const Scene const* scene;
	

public:
	/// @brief Creates a new window
	/// @param controller - The input controller to use for input processing
	/// @param w - Number of pixels in width
	/// @param h - Number of pixels in height
	/// @param VSync - Whether Vertical Synchronization is enabled
	/// @param fullscreen - Whether to create it in fullscreen
	Window(InputManager& controller, int w = 800, int h = 600, bool VSync = 0, bool fullscreen = 0);
	~Window();

	/// @brief  updates the window screen with the current scene state
	/// @return float - frame time
	float update();	//parameter dt doesn't belong here, it belongs to the physics affecting the scene.
	void handle_events(); ///Will have to be moved to a supposed Window Manager	
	
	/// @brief Potentially misleading name. This is the code executed each frame by the window
	void shader();
	inline const bool get_validity() const noexcept  { return valid; }
	int set_fps(unsigned int fps) noexcept;

	/// @brief Get dimensions of the window
	/// @return vec2d{width, height}
	vec2d get_size() { return {(float)w, (float)h}; };

	//Only cares about the Mesh component of the entity. !! MAY NOT KNOW IF THE OBJECT WAS DELETED !!
	
	/// @brief Sets the scene to observe and render
	/// @param &s - Scene to display
	/// @return Whether the scene is populated
	bool set_active_scene(Scene &s);
};
