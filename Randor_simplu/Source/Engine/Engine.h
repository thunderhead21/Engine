#pragma once

#include "Components/Components.h"
#include "Core/Core.h"

#include <time.h>
#include <random>


//Provide possibility to use and external timer. This
//This can be useful in on-demand simulation pacing
//Example - For debug purposes, you want dt to be 10x larger, 
//so that the simulation time is accelerated to check for 
//strange behaviour or KSP-like "Krakens"

// [DESIGN]
// World updates are performed through the Engine update loop.
//
// Event processing, simulation and rendering are coordinated
// from a single update path to avoid duplicated execution.


class Engine
{
protected:

	std::mt19937 rng{ (unsigned int)time(nullptr) };
	std::uniform_real_distribution<float> pos{ -2000.f, 2000.f };
	std::uniform_real_distribution<float> size{1.f, 500.f};

	Timer timer;
	Scene world;
	InputManager controller;
	Window renderer;

	void create_default_keybindings();
	void initialize_keybindings(std::string filename);

public:

	Engine(std::string window_name = "New Vigineer Window", unsigned int res_x = 1280, unsigned int res_y = 960, bool VSync = 1, bool fullscreen = 0);
	~Engine() = default;
	
	void refresh_scene();

	float update();
	float update(float dt);

	/////////// FACTORIES ///////////
	void add_cube(bool phys_enabled = 1, unsigned int side = 400, size_t count = 1);
	void add_rectangle(bool phys_enabled = 1, unsigned int width = 300, unsigned int height = 150, size_t count = 1);
	void add_triangle(bool phys_enabled = 1, unsigned int width = 300, unsigned int height = 300, size_t count = 1);

};

