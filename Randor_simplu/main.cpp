//#define SDL_MAIN_HANDLED


//#include <SDL3/SDL.h> included by the others
//#include "Window.h"

#include "Core/FrameStat/FrameStat.h"
#include "Components/Components.h"
#include "Tests/UTests.h"
#include <random>



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
void rendering_test_run(unsigned int fps = 60, float seconds = 15, unsigned int ignore_frames = 10){

	seconds = fabs(seconds);

	FrameStat fs;
	InputManager i;

	Window w(i);
	w.set_fps(fps);

	static unsigned int probe = 0;
	unsigned int dbg_frames = (fps * seconds) + ignore_frames;

	SDL_Event event;



	Scene s;

	std::mt19937 rng(time(nullptr));
	std::uniform_real_distribution<float> pos(-2000.f, 2000.f);
	std::uniform_real_distribution<float> size(1.f, 500.f);
	

	int test_entities_count = 300000;
	s.reserve(test_entities_count);
	
	for (int i = 0; i < test_entities_count; i++) {
		s.add_entity(new RigidBody(RigidBody::Cube(400)));

	}

	/*

	for (auto& entity : s) {


		if (RigidBody* body = dynamic_cast<RigidBody*>(entity)) {

			//body->set_angular_velocity({ (float)(rand() % 30), (float)(rand() % 30), (float)(rand() % 30) });

			//body->set_velocity( { (float)(rand() % 30), (float)(rand() % 30) , (float)(rand() % 30) } 

			//body->transform().position({ pos(rng), pos(rng) , pos(rng)});

		}
		
	}
		
	*/

	s.rebuild_queues();
	w.set_active_scene(s);
	
	float elapsed = 0;

	while (w.get_validity() && elapsed < seconds) {
		SDL_PollEvent(&event);

		float dt = w.update();
		elapsed += dt;

		//s.update(dt);
		probe++;

		if (probe < ignore_frames) {
			std::cout << dt << '\n';
		}
		if (probe >= dbg_frames ) {
			break;
		}
	
		fs.add(dt);
	}
	fs.print();
	std::cin.get();

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

	rendering_test_run(60, 30, 10);
	Timer t;

	//std::cin.get();

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
	
	Entity* e1 = new RigidBody(RigidBody::Cube(250));
	Entity* e2 = new RigidBody(RigidBody::Cube(350));
	Entity* e3 = new RigidBody(RigidBody::Cube(450));

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

		float dt = w.update();
		world.update(dt);
		i.update(event);
		fs.add(dt);

		//w.handle_events();	//Obsolete... (?) -- Kind of... Now is done once we update the screen
		

	}

	fs.print();

	return 0;
}