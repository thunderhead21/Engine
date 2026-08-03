#pragma once

#include "../Components/Components.h"

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
	Timer timer;
	Scene world;
	Window renderer;
	InputManager controller;

public:

	Engine(std::string window_name);
	~Engine() = default;


	float update();
	float update(float dt);

};

