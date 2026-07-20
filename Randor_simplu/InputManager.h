#pragma once

#include <unordered_map>	//Keymap proper
#include <set>
#include <functional>
#include "Keybind.h"

//Is it really a void funct() ?
using Action = std::function<void()>;
using Keymap = std::unordered_map<Keybind, Action, KeybindHash, KeybindEqual>;

/// @brief Manages or makes available everything regarding input from interfacing devices (e.g - mouse, keyboard, joystick...)
/// @brief Allows declaring a keybinding or accessing the state of the key directly
/// @brief Manages or makes available everything regarding input from interfacing devices (e.g - mouse, keyboard, joystick...)
class InputManager
{	
private:

	// The golden formula to ignore modifiers
	//lookup_key.required_mods = e.mod & ~(SDL_KMOD_NUM | SDL_KMOD_CAPS | SDL_KMOD_SCROLL);

	Keymap keymap;
	std::set<SDL_Keymod> ignored;
	SDL_Keymod ignore_mask = 0;

	bool* kb_state;

	const bool* get_keyboard_state();
	void update_keyboard_state();
public:
	/// @brief Default Ctor
	InputManager() noexcept;

	/// @brief Copy Ctor. Populate members from other InputManager
	/// @param other InputManager to copy
	InputManager(const InputManager& other) noexcept;
	
	/// @brief Copy Ctor. Get bindings from existing map
	/// @param existing_keymap Map to incorporate into input manager
	InputManager(Keymap& existing_keymap) noexcept;

	/// @brief Default Dtor
	~InputManager();

	void update(SDL_Event &e);

	/// @brief Create keybinding from ready objects
	/// @param key Keybind object tied that triggers the action
	/// @param action function pointer to call when key is pressed
	void register_keybind(const Keybind& key, Action action) noexcept;


	/// @brief Create Keybinding from basic data. 
	/// @param key Key to assign to action
	/// @param action (void*)() to function callback
	/// @param required Optional. Modifiers necessary alongside key 
	/// @param illegal Optional. Modifiers that nullify the binding (if shift is pressed, cancel)
	void register_keybind(SDL_Scancode key, Action action, SDL_Keymod required = SDL_KMOD_NONE) noexcept;

	/// @brief Attempts to add the Keymod to the set of ignored mods.
	/// @param mod - Modifier to ignore if it wasn't already ignored
	bool ignore_keymod(SDL_Keymod& mod);

	/// @brief Attempts to eliminate the Keymod to the set of ignored mods.
	/// @param mod - Modifier to allow affecting keybindings
	bool process_keymod(SDL_Keymod& mod);

	/// @brief Checks for a key in the keymap collection and passes control to the associated function by pointer.
	/// @param key the key to check for in the mapping
	/// @return boolean value TRUE if the key was found in the existing keybindings. Otherwise, false.
	const bool process_key(SDL_KeyboardEvent key) noexcept;
	
	/// @brief Checks current key state for a given key
	/// @param key to get state of
	/// @return TRUE if the key is pressed (active). FALSE if the key is not pressed (inactive) 
	bool is_active(SDL_Scancode key) noexcept;

	

};

