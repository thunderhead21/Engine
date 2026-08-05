//#define SDL_MAIN_HANDLED


#include <random>
#include <fstream>

#include "Core/FrameStat/FrameStat.h"
#include "Components/Components.h"
#include "Tests/UTests.h"
#include "Engine/Engine.h"

#include <Psapi.h>
#include <Windows.h>

std::size_t get_ram_usage_mb()
{
	PROCESS_MEMORY_COUNTERS_EX pmc{};

	if (GetProcessMemoryInfo(
		GetCurrentProcess(),
		reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc),
		sizeof(pmc)))
	{
		return pmc.WorkingSetSize / (1024 * 1024);
	}

	return 0;
}

/*
NEXT STEP - Create pipeline :

Vec4d - > [? Vec3d ?] - > SDL_Vertex
Vec3d - > [vec2d{x/z, y/z}] - > SDL_Vertex
Implement valid conversion from Vec2d to vertex
Implement simple pipeline (ie Vec4d_to_Vertex())
Colour helpers

Continue the math library - Matrix implementation, vector multiplications, matrix multiplication

Finish the transform class

Implement the projection system

Transformation queuing


*/


/// @brief Renderer a test scene [scene not implemented]
/// @param fps - The desired framerate of the simulation
/// @param seconds - Amount of time to run the scene for
/// @param ignore_frames - Skip registering frame times for
void rendering_test_run(unsigned int entities = 10000, unsigned int fps = 60, float seconds = 15, unsigned int ignore_frames = 10) {

	seconds = fabs(seconds);

	FrameStat fs;
	InputManager i;

	Window w(i, 1440, 720, true);
	w.set_fps(fps);

	SDL_Event event;
	Scene s;

	std::mt19937 rng(time(nullptr));
	std::uniform_real_distribution<float> pos(-2000.f, 2000.f);
	std::uniform_real_distribution<float> size(1.f, 500.f);



	s.reserve(entities);

	for (int i = 0; i < entities; i++) {
		s.add_entity(RigidBody::Cube(400));

	}



	for (auto& entity : s) {


		if (RigidBody* body = dynamic_cast<RigidBody*>(entity)) {

			body->set_angular_velocity({ size(rng), size(rng), size(rng) });

			body->set_velocity({ pos(rng), pos(rng) , pos(rng)});

			body->transform().position({ pos(rng), pos(rng) , pos(rng) });

		}

	}



	s.rebuild_queues();
	w.set_active_scene(s);

	float elapsed = 0;
	unsigned int probe = 0;
	float dt = 0, sim_dt = 0;
	while (w.get_validity() && elapsed < seconds) {
		SDL_PollEvent(&event);

		dt = w.update().last();
		elapsed += dt;

		sim_dt += s.update(dt);

		if (probe < ignore_frames) {
			std::cout << dt << '\n';
			probe++;
		}

		fs.add(dt);
	}
	sim_dt = (sim_dt / (fs.runtime() * fs.average_fps())) * 1000;

	std::ofstream f("Benchmark_history.log", std::ios::app | std::ios::out);
	spdlog::info("{} entities", s.get_entities().size());
	spdlog::info("Average physics time: {}ms", sim_dt);

	fs.print();
	f << s.get_entities().size() << " entities simulated.\n";
	f<<"Average physics time:" << sim_dt<<"ms" << fs.str();
	f << get_ram_usage_mb() << " MB RAM\n\n";
	

}

unsigned char gear = 0;

void SHIFT_DN() {
	
	if (gear > 0) {
		gear--;
		std::cout << "Shifted down - GEAR " << (int)gear << std::endl;
	}
	else std::cout << "Cannot shift down - GEAR " << (int)gear << std::endl;

}

void SHIFT_UP() {

	if (gear < 6) {
		gear++;
		std::cout << "Shifted up - GEAR " << (int)gear << std::endl;
	}
	else std::cout << "Cannot shift up - GEAR " << (int)gear << std::endl;

}

template <typename T>
void print_mat(mat<T>& m) {

	//std::cout << "Size = " << s;
	for (int i = 0; i < m.columns; i++) {
		for (int j = 0; j < m.rows; i++) {
			 std::cout << m[i]<< ' ';
		}
		std::cout << '\n';
	}
}

// [ARCHITECTURE]
// Entities belong to the Scene.
//
// Window/Engine may observe or render the world,
// but Scene remains the authoritative owner of all world objects.
// 
// /////////////////////////////////////////////////
// 
// Transform is the single source of truth for spatial state.
//
// Mesh never owns position, rotation or scale.
// Rendering always consumes Entity::Transform.

//Now you have to pass the input manager to the window as function parameter for topical usage
int main(int argc, char* argv[])
{
	Engine engine;

	engine.add_cube();
	engine.add_cube();
	engine.refresh_scene();

	while (engine.update());

	for (int i = 1000; i < 80000; ) {
		rendering_test_run(i, 120, 30);
		if (i < 10000) i += 2000;
		else if (i < 50000) i += 10000;
		else i += 20000;
		SDL_Delay(2000);
	}
	Timer t;

	std::cin.get();

	bool run_tests = 0;
	if (run_tests) {
		TEST_vec2d_length();
		TEST_vec3d_length();
		TEST_vec4d_length();

		TEST_vec2d_square();
		TEST_vec3d_square();
		TEST_vec4d_square();

		TEST_vec2d_vertex();
		TEST_vec3d_vertex();
		TEST_vec4d_vertex();

		TEST_platform_scheduler_precision(10, 1000);

		//std::cin.get();
	}

	InputManager i;

	/*
	Cube c1(150);
	Cube c2(50);
	Cube c3(80);
	*/
	
	Entity* e1 = RigidBody::Cube(250);
	Entity* e2 = RigidBody::Cube(350);
	Entity* e3 = RigidBody::Cube(450);

	Window w(i, 1280, 720, false);
	w.set_fps(120);

	e1->enable_layer(Layers::Physics | Layers::Renderable);
	
	//Using thin wrapper
	i.register_keybind(SDL_SCANCODE_Q, SHIFT_DN);
	i.register_keybind(SDL_SCANCODE_E, SHIFT_UP);
	i.register_keybind(SDL_SCANCODE_BACKSLASH, []{__debugbreak(); });

	e1->transform().position({ 500, 300, -02 });
	e2->transform().position({ 800, 600, 10 });
	e3->transform().position({ -100, 500, 00 });

	Scene world;
	std::vector<Entity*> ents{new Entity(Cube(100)), new Entity(Cube(50)), new Entity(Cube(200))};
	world.add_entity(ents);

	RigidBody* rb1 = dynamic_cast<RigidBody*>(world.add_entity(new RigidBody(Cube(370))));
	(*rb1).set_angular_velocity({ 10.0f, 30.0f, 0.0f });
	(*rb1).set_velocity({100.0f, 100.0f, 0.0f});

	RigidBody* rb2 = dynamic_cast<RigidBody*>(world.add_entity(new RigidBody(Cube(370))));
	(*rb2).set_angular_velocity({ 10.0f, 30.0f, 0.0f });
	(*rb2).set_velocity({ -100.0f, -100.0f, 0.0f });

	world.add_entity({e1, e2, e3});
	rb2->transform().position() = {-1000, 0, 0};

	/* Outdated, entities belong to the scene
	w.enroll_entity(e1);
	w.enroll_entity(e2);
	w.enroll_entity(e3);
	*/

	world.rebuild_queues();
	if(w.set_active_scene(world)) spdlog::critical("WORLD IS EMPTY!");


	FrameStat fs;
	SDL_Event event;
	while (w.get_validity()) {
		SDL_PollEvent(&event);													///Event is the hooker you pass around O.O

		float dt = w.update().last();
		world.update(dt);
		i.update(event);
		fs.add(dt);

		//w.handle_events();	//Obsolete... (?) -- Kind of... Now is done once we update the screen
		

	}

	fs.print();
	SDL_Quit();
	return 0;
}