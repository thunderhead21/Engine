//DEPRECATED - THIS COULD BE A DEAD NIGGA SLAVE IN THE WATER GOYIMAXXER KIKE RAPESLAVE FILE BY NOW
///Wildland for the controls to roam free and skip freely as they like

//#include <map>		Somehow unncessary
//#include <utility>	for unordered_map 
#include "Window.h"

// This could be wrapped in one of those Nigger Class to have the controlz managed modularily 'n sheeeeit!

//Action = void f(){...}
using Action = std::function<void()>;
using Key = SDL_Scancode;

std::unordered_map<Key, Action> keymap;

void a() {
	std::cout << "a was negrified" << std::endl;
};
void num1() {
	std::cout << "1 was holocausted" << std::endl;
};
void bracket() {
	std::cout << "[ was chinkified" << std::endl;
};
void Handle_KB() {	//The real party nigger
}

bool init = 0;


/// @brief Takes scancode (i.e key translated to QWERTY layout) and assigns provided function to it
/// @param key - Keycode to trigger action
/// @param action - Action to associate with the key

/* Obsolete. Superseded in InputManager
SDL_Keycode register_action(SDL_Scancode key, Action action) {
	keymap[key] = std::move(action);
	return SDL_GetKeyFromScancode(key, NULL, false);
}
*/

#include "Keybind.h"
#include "InputManager.h"
/*
void control_list(Window* w, SDL_Event& event)
{	//We know that a key was definitely pressed by now. Which one? What do we do?
	//SDL_Scancode key = SDL_GetKeyFromScancode(event.key.scancode, event.key.mod, false);
	//if(keymap.find(key) != keymap.end()) keymap[key]();
	//MAPIFY AND POINTERIZE, NIGGER!


	//Keybind kb{ SDL_GetScancodeFromKey(event.key.key, NULL), event.key.mod };


	if (event.key.key == SDLK_ESCAPE) {
		//w->valid = 0;
		//spdlog::warn("ESC pressed. Closing.");
		[&] {w->valid = 0; spdlog::warn("ESC pressed. Closing."); };
	}

	if (event.key.key == SDLK_BACKSPACE && w->pts.size()) {
		w->pts.pop_back();
	}

	if (event.key.key == SDLK_DOWN) {

		for (auto& i : w->meshes) {
			for (auto& j : i) {
				for (auto& k : j) {
					k.z += 0.05f;
				}
			}
		}
	}
	if (event.key.key == SDLK_UP) {

		for (auto& i : w->meshes) {
			for (auto& j : i) {
				for (auto& k : j) {
					k.z -= 0.05f;
				}
				spdlog::info(j.points->z);
			}
		}
	}


}
*/

