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



std::vector<SDL_Vertex> vertices;
bool converted = 0;

void Mesh_to_vertices(Mesh& m) {

	vertices.clear();

	int a = 200, r = 2, g = 40, b = 15;


	float base = (1.0f / 255.0f);

	for (auto &t : m.get_vertices()) {	//For each vertex of the Mesh

		SDL_Vertex v = t.vertex();

		v.color.a = base * (a % 255);
		v.color.r = base * (r % 255);
		v.color.g = base * (g % 255);
		v.color.b = base * (b % 255);

		a += 15;
		r += 30;
		g += 52;
		b += 15;


		vertices.push_back(v);
		
		
		
	}
}

void Window::shader() {


	for (auto& entity : entities) {
		std::vector<vec4d> world_vertices = entity->get_transform() * entity->get_Mesh();

		std::vector<SDL_Vertex> render_vertices;
		render_vertices.reserve(world_vertices.size());

		for (const auto& vertex : world_vertices) {
			SDL_Vertex sdl_vertex = flat_projection({vertex.x, vertex.y, vertex.z});
			sdl_vertex.color.r = 1.0f;
			sdl_vertex.color.g = 1.0f;
			sdl_vertex.color.b = 1.0f;
			sdl_vertex.color.a = 1.0f;
			
			render_vertices.push_back(sdl_vertex);
		}

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

