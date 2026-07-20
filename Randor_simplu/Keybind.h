#pragma once
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_events.h>
#include <functional>


//Nice and easy. Make it as simple and uncomplicated it is boring to read!


/// @brief Key abstraction.
/// @brief stores the key, required modifiers and escape mods 
struct Keybind {

	SDL_Scancode key = SDL_SCANCODE_UNKNOWN;
	SDL_Keymod required_mods = SDL_KMOD_NONE;

	/// @brief Checks if the keybinding was triggered
	/// @param e SDL_KeyboardEvent to check
	/// @return bool value true if the binding was triggered. False otherwise
	bool matches(const SDL_KeyboardEvent& e) const;

	/// @brief Checks if two keybindings are equal
	/// @param other Keybind to compare against
	/// @return True if all members are the same
	bool operator==(const Keybind& other) const;

};

struct KeybindEqual {

	bool operator()(const Keybind& a, const Keybind& b) const;

};

//E
struct KeybindHash {
	/// @brief Hash creation functor
	/// @param kb keybind to compute hash for
	/// @return size_t hash value
	size_t operator()(const Keybind& kb) const;
};

//	bool binding_equal(const Keybind& a, const Keybind& b); OBSOLETE - Mexican Operator==() tooks its job