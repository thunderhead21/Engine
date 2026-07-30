#pragma once

#include "Components.h"

//Provide possibility to use and external timer. This
//This can be useful in on-demand simulation pacing
//Example - For debug purposes, you want dt to be 10x larger, 
//so that the simulation time is accelerated to check for 
//strange behaviour or KSP-like "Krakens"
//


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

