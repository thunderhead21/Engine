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
	///vec3d p1{ 284, 25, 300 }, p2{ 80, 70, 0 }, p3{ 230, 50, 125 };		//To be removed
	///std::vector<Mesh> meshes;	///To be removed
	
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
	/*
	std::vector<SDL_FRect> rects = { {30, 30, 100, 500}, {820, 500, 148, 188}, {0, 0, 0, 0} };
	SDL_FRect* tmp = &rects.at(2);
	std::vector<SDL_FPoint> pts = { {2, 2},{ p1.x + p1.z / 2.0f, p1.y + p1.z / 2.0f }, { p3.x + p3.z / 2.0f, p3.y + p3.z / 2.0f } };
	*/
	

	Window(InputManager& controller, int w = 800, int h = 600, bool VSync = 0, bool fullscreen = 0);
	~Window();
	void update();

	void handle_events(); ///Will have to be moved to a supposed Window Manager	

	void shader();
	inline const bool get_validity() const noexcept  { return valid; }
	inline int set_fps(unsigned int fps) noexcept { this->fps = fps; return this->fps; }
	inline const void set_input_manager(InputManager& controller) noexcept { controller = controller; };
	//SDL_Rect& draw_rectangle();

	//Only cares about the Mesh component of the entity. !! MAY NOT KNOW IF THE OBJECT WAS DELETED !!
	Mesh& load_entity_mesh(Entity& ent);	//INACTIVE

	Entity* enroll_entity(Entity &ent);
};
