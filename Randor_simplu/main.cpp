//#define SDL_MAIN_HANDLED


//#include <SDL3/SDL.h> included by the others
//#include "Window.h"

#include "UTests.h"
#include "Window.h"
#include "InputManager.h"
#include "Matrix.hpp"
#include "rectangle.h"
#include "triangle.h"

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

//Entity a;

//Now you have to pass the input manager to the window as function parameter for topical usage
int main(int argc, char* argv[])
{
	

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

		std::cin.get();
	}

	InputManager i;

	rectangle r(100.0f, 100.0f);
	triangle t({600, 300, 0}, { 300, 900, 0 }, { 900, 900, 0 });
	Entity e1(r);
	Window w(i);
	//w.load_entity_Mesh(e);
	
	SDL_Event event;
	
	//Using thin wrapper
	i.register_keybind(SDL_SCANCODE_Q, SHIFT_DN);
	i.register_keybind(SDL_SCANCODE_E, SHIFT_UP);
	i.register_keybind(SDL_SCANCODE_BACKSLASH, []{__debugbreak(); });

	e1.get_transform().set_position({ 500, 300, 00 });

	w.enroll_entity(e1);

	while (w.get_validity()) {
		SDL_PollEvent(&event);	///Event is the hooker you pass around O.O

		w.update();
		w.handle_events();	//Obsolete... (?)

		i.update(event);


		

		SDL_Delay(10);
	}


	return 0;
}