#include "InputManager.h"


/*	UNUSED. Debug if there are errors regarding this

void InputManager::update_keyboard_state()
{
	*kb_state = (bool*)SDL_GetKeyboardState(nullptr);
}
*/

InputManager::InputManager() noexcept:
	keymap(Keymap()), ignored({ SDL_KMOD_NUM, SDL_KMOD_CAPS, SDL_KMOD_SCROLL})
{

	kb_state = (bool*)SDL_GetKeyboardState(nullptr); 

	for (auto& i : ignored) {

		ignore_mask |= i;

	}


}
InputManager::InputManager(const InputManager& other) noexcept:
	keymap(other.keymap), ignored(other.ignored)
{
	*kb_state = *other.kb_state;	//Potential edge case handling - Constant keyboard state that needs to be preserved
	for (auto& i : ignored) {

		ignore_mask |= i;

	}
}

InputManager::InputManager(Keymap& existing_keymap) noexcept :
	keymap(Keymap(existing_keymap))
{
	*kb_state = (bool*)SDL_GetKeyboardState(nullptr);
	for (auto& i : ignored) {

		ignore_mask |= i;

	}
}

InputManager::~InputManager()
{

}

void InputManager::register_keybind(const Keybind& key, Action action) noexcept
{
	Keybind kb{ key };
	keymap[kb] = std::move(action);


}

void InputManager::register_keybind(SDL_Scancode key, Action action, SDL_Keymod required) noexcept
{
	Keybind kb{ key, required };
	keymap[kb] = std::move(action);
}

bool InputManager::ignore_keymod(SDL_Keymod& mod)
{
	bool inserted = ignored.insert(mod).second; //If the vector contains the modifier we want to ignore, nothing to be done
	ignore_mask |= mod;

	return inserted;
}

bool InputManager::process_keymod(SDL_Keymod& mod)
{
	/*
	* 00101010 &
	* 11011111
	* --------
	* 00001010
	*/

	ignore_mask &= ~mod;		//Eliminate the modifiers from the mask	-- NOTE: Does not require rebuilding of the mask from the set!

	return ignored.erase(mod);	//Eliminate the modifiers from the set
}



const bool InputManager::process_key(SDL_KeyboardEvent kb_event) noexcept
{

	//lookup_key.required_mods = e.mod & ~(SDL_KMOD_NUM | SDL_KMOD_CAPS | SDL_KMOD_SCROLL);
	Keybind key{ kb_event.scancode, kb_event.mod };
	key.required_mods &= ~ignore_mask;	//Filter the bits matching the ignored modifiers

	if ((keymap.find(key) != keymap.end())) {	//If there was an element found belonging to the key pressed

		keymap.at(key)();	//Pass control
		return 1;			//Signal binding hit
	}
	return 0;
}
bool InputManager::is_active(SDL_Scancode key) noexcept {
	return kb_state[key];
}
/// @brief Updates internal keyboard state. Checks if there is a binding registered for the key that was pressed
/// @param e - SDL_Event reference to be processed
void InputManager::update(SDL_Event &e) {
	if (e.type != SDL_EVENT_KEY_DOWN) return;
	do  
	{
		if (e.type == SDL_EVENT_KEY_DOWN) {
			Keybind check{ e.key.scancode, e.key.mod };
			//lookup_key.required_mods = e.mod & ~(SDL_KMOD_NUM | SDL_KMOD_CAPS | SDL_KMOD_SCROLL);

			auto it = keymap.find(check);
			if (it != keymap.end()) it->second();
		}
	} while (SDL_PollEvent(&e));
}
