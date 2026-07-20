#include "Window.h"

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

	for (auto &t : m.tris) {	//For each triangle of the Mesh
		for (int i = 0; i < 3; i++) {	//Store the coordinates of each point
			SDL_Vertex v = t.points[i].vertex();

			/*
			const vec3d& p = t.points[i];

			v.tex_coord.x = v.position.x = p.x / p.z;
			v.tex_coord.y = v.position.y = p.y / p.z;
			*/
			
			

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
}

void Window::shader() {

	if (!converted) {

		for (auto& i : entities) {
				Mesh_to_vertices(i->get_Mesh());
				//i->apply_transform();

		}
	}



	if (SDL_RenderGeometry(renderer, nullptr, vertices.data(), (int)vertices.size(), nullptr, 0) == false) {
		std::cout << SDL_GetError() << '\n';
	};

}

