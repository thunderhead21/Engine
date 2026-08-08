#include "Projection/Projection.h"
#include "Components/Window/Window.h"

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


float sx=0.15f, sy=0.15f, sz=0.15f;
float a = 205, r = 255, g = 135, b = 3;
float base = (1.0f / 255.0f);
bool ascending = 1;

// [ARCHITECTURE]
// Transform is the single source of truth for spatial state.
//
// Mesh never owns position, rotation or scale.
// Rendering always consumes Entity::Transform.


#if FRAME_PROFILER
	Timer  shader_timer;
	double rendering = 0, tform = 0, projection = 0;	//Timing variables
#endif
void Window::shader() {
	// [DESIGN]
	// Scale belongs to Transform.
	//
	// Physics may consume scale (for collision volumes),
	// but Transform remains the authoritative owner.
#if FRAME_PROFILER

	rendering = 0, tform = 0, projection = 0;	//Reset Timing variables
	shader_timer.reset();
#endif
	if (scene == NULL) {
		spdlog::warn("\"{}\" has no scene to render", SDL_GetWindowTitle(this->window));
		return;
	}
	//Changes scale by pressing < or >
	if(controller.is_active(SDL_SCANCODE_PERIOD)) {
			
		sx += 0.9f * profiling.last() + (sx / 50);
		sy += 0.9f * profiling.last() + (sy / 50);
		sz += 0.9f * profiling.last() + (sz / 52);
			
	}

	if (controller.is_active(SDL_SCANCODE_COMMA) && sx + sy + sz > 0) {
			
		sx -= 0.9f * profiling.last() + (sx / 50);
		sy -= 0.9f * profiling.last() + (sy / 50);
		sz -= 0.9f * profiling.last() + (sz / 52);
		
	}



	for (const auto &entity : scene->get_visible_entities()) {
		

		entity->transform().scale({ sx, sy, sz });		//SUPERSEDED BY SCENE.PHYSICS -- FALSE! Controlling scale is optimal here!
		//entity->get_transform().rotate({ 0.1f, 0.0f, 1.0f });	[30.07.2026] Changed function to transform


		//Recompute the entity if it changed
		if (entity->transform().changed()) {

			entity->projection_buffer().clear();
			entity->world_buffer().clear();
			
			//Transforms the vertices to world space and places them in the world
			entity->transform().transform_mesh(entity->mesh(), entity->world_buffer());	//This is the result of operator*() in the middle!. It is good the two functions return a reference

#if FRAME_PROFILER
			tform += shader_timer.tick();
#endif // FRAME_PROFILER

			// [DESIGN]
			// Rendering operates on world-space geometry.
			//
			// Mesh stores local-space geometry.
			// Transform converts local geometry into world space
			// immediately before rendering.

			//Projected vertices onto the screen.
			entity->projection_buffer().reserve(entity->world_buffer().size());	//Naturally, we already know how many of them we are going to have
			for (const auto& vertex : entity->world_buffer()) {		//Take each one and project it!

				//Pass the screen size so we know to center them
				weak_projection(this->get_size(), { vertex.x, vertex.y, vertex.z }, entity->projection_buffer());

				entity->projection_buffer().back().color.r = (r * base);	///And apply some global default colour
				entity->projection_buffer().back().color.g = (g * base);
				entity->projection_buffer().back().color.b = (b * base);
				entity->projection_buffer().back().color.a = (a * base);
			
				
			}
			entity->clean();
#if FRAME_PROFILER

			projection += shader_timer.tick();
#endif // FRAME_PROFILER
		}
		//And finally, render what we have!
		if (SDL_RenderGeometry(
			renderer, 
			nullptr, 
			entity->projection_buffer().data(),
			entity->projection_buffer().size(),
			(const int*)entity->mesh().indices().data(), 
			entity->mesh().indices().size()) == false) {
			std::cout << SDL_GetError() << '\n';
		};

#if FRAME_PROFILER
		rendering += shader_timer.tick();
#endif // FRAME_PROFILER

	}

#if FRAME_PROFILER
	profiling.render_tform_time(tform);
	profiling.projection_time(projection);
	profiling.render_time(rendering);

	/*
	spdlog::info("TForm: {}ms", tform);
	spdlog::info("Projection: {}ms", projection);
	spdlog::info("rendering: {}ms\n", rendering);
	*/
	

#endif // FRAME_PROFILER

}

