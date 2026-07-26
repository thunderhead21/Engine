#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "Entity.h"
#include "InputManager.h"

constexpr bool DEBUG = 0;
constexpr bool INFO = 0;

/*
namespace Input {
#define LMB SDL_BUTTON_MASK(SDL_BUTTON_LEFT)
#define RMB SDL_BUTTON_MASK(SDL_BUTTON_RIGHT)
#define MMB SDL_BUTTON_MASK(SDL_BUTTON_MIDDLE)
#define FMB SDL_BUTTON_MASK(SDL_BUTTON_X1)
#define BMB SDL_BUTTON_MASK(SDL_BUTTON_X2)
}
*/



class Entity;
struct vec3d;

class Window
{

	
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

	bool init();
	void register_own_keybindings();

	std::vector<Entity*> entities;

public:

	Window(InputManager& controller, int w = 800, int h = 600, bool VSync = 0, bool fullscreen = 0);
	~Window();

	void update();
	void handle_events(); ///Will have to be moved to a supposed Window Manager	

	void shader();
	inline const bool get_validity() const noexcept  { return valid; }
	inline int set_fps(unsigned int fps) noexcept { this->fps = fps; return this->fps; }

	/// <summary>
	/// Get dimensions of the window
	/// </summary>
	/// <returns>vec2d{width, height}</returns>
	vec2d get_size() { return {(float)w, (float)h}; };

	//Only cares about the Mesh component of the entity. !! MAY NOT KNOW IF THE OBJECT WAS DELETED !!

	Entity* enroll_entity(Entity &ent);
};
