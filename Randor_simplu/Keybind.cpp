#include "Keybind.h"



bool Keybind::matches(const SDL_KeyboardEvent& e) const {
	if (e.scancode != key) return false;

	
	return (e.mod & required_mods) == required_mods;
}


bool Keybind::operator==(const Keybind& other) const {
	return key == other.key && (required_mods & other.required_mods) == other.required_mods;
}

bool KeybindEqual::operator()(const Keybind& a, const Keybind& b) const {
	return a == b;	//Works because operator==() was defined by Keybind
}

size_t KeybindHash::operator()(const Keybind& kb) const {
	size_t h1 = std::hash<SDL_Scancode>()(kb.key);
	size_t h2 = std::hash<Uint16>()(static_cast<Uint16>(kb.required_mods));

	return h1 ^ h2 << 1;

}
