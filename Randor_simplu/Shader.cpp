#include "Window.h"
#include "Projection.h"

/* Click to add line to render queue. Nice little demo
float r = 220, g = 230, b = 225;
float vr = 0.070, vg = 0.069, vb = 0.046;

void Window::shader() {

	if (r <= 3.0f || r >= 253.0f) vr = -vr;
	if (g <= 3.0f || g >= 253.0f) vg = -vg;
	if (b <= 3.0f || b >= 253.0f) vb = -vb;

	r += vr;
	g += vg;
	b += vb;

	
	SDL_SetRenderDrawColor(renderer, (int)r, (int)g, (int)b, 255);
	SDL_RenderRects(renderer, rects.data(), rects.size());

	SDL_RenderLines(renderer, pts.data(), pts.size());
}
*/


float sx=0.85f, sy=0.85f, sz=0.85f;
float a = 125, r = 185, g = 50, b = 80;
float base = (1.0f / 255.0f);
bool ascending = 1;



void Window::shader() {



	for (const auto &entity : *scene) {

		entity->transform().set_scale({ sx, sy, sz });		//SUPERSEDED BY SCENE.PHYSICS -- FALSE! Controlling scale is optimal here!
		//entity->get_transform().rotate({ 0.1f, 0.0f, 1.0f });	[30.07.2026] Changed function to transform


		//Changes scale by pressing < or >
		if(controller.is_active(SDL_SCANCODE_PERIOD)) {
			
			sx += 0.1f;
			sy += 0.1f;
			sz += 0.1f;
			
		}

		if (controller.is_active(SDL_SCANCODE_COMMA)) {
			
			sx -= 0.1f;
			sy -= 0.1f;
			sz -= 0.1f;
		
		}

		//Transforms the vertices to world space
		std::vector<vec4d> world_vertices = entity->transform() * entity->get_Mesh();

		//Projected vertices onto the screen
		std::vector<SDL_Vertex> render_vertices;
		render_vertices.reserve(world_vertices.size());	//Naturally, we already know how many of them we are going to have
		for (const auto& vertex : world_vertices) {		//Take each one and project it!

			//Pass the screen size so we know to center them
			SDL_Vertex sdl_vertex = weak_projection(this->get_size(), {vertex.x, vertex.y, vertex.z});
			sdl_vertex.color.r = (r * base);	///And apply some global default colour
			sdl_vertex.color.g = (g * base);
			sdl_vertex.color.b = (b * base);
			sdl_vertex.color.a = (a * base);
			
			render_vertices.push_back(sdl_vertex);	
		}

		//And finally, render what we have!
		if (SDL_RenderGeometry(
			renderer, 
			nullptr, 
			render_vertices.data(), 
			render_vertices.size(), 
			(const int*)entity->get_Mesh().get_indices().data(), 
			entity->get_Mesh().get_indices().size()) == false) {
			std::cout << SDL_GetError() << '\n';
		};
				
					

	}


}

