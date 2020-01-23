#ifndef INCLUDED_KEYNAME
#define INCLUDED_KEYNAME

// Need SDLK_* enum values.
#include "../lib/external_libraries/libsdl.h"

class CStr8;

extern void InitKeyNameMap();
extern CStr8 FindKeyName(int keycode);
extern int FindKeyCode(const CStr8& keyname);

enum {
	// Start sequential IDs in the right place
	// Pick a code which is greater than any keycodes used by SDL itself
	EXTRA_KEYS_BASE = SDL_SCANCODE_TO_KEYCODE(SDL_NUM_SCANCODES),
	// 'Keycodes' for the unified modifier keys
	UNIFIED_SHIFT,
	UNIFIED_CTRL,
	UNIFIED_ALT,
	UNIFIED_SUPER,
	UNIFIED_LAST,
	// 'Keycodes' for the mouse buttons
	// Base for mouse buttons.
	// Everything less than MOUSE_BASE is not reported by an SDL mouse button event.
	// Everything greater than MOUSE_BASE is reported by an SDL mouse button event.
	MOUSE_BASE,
	MOUSE_LEFT = MOUSE_BASE + SDL_BUTTON_LEFT,
	MOUSE_MIDDLE = MOUSE_BASE + SDL_BUTTON_MIDDLE,
	MOUSE_RIGHT = MOUSE_BASE + SDL_BUTTON_RIGHT,
	// SDL2 doesn't count wheels as buttons, so just give them the previous sequential IDs
	MOUSE_WHEELUP = MOUSE_BASE + 4,
	MOUSE_WHEELDOWN = MOUSE_BASE + 5,
	MOUSE_X1 = MOUSE_BASE + SDL_BUTTON_X1 + 2,
	MOUSE_X2 = MOUSE_BASE + SDL_BUTTON_X2 + 2,
	MOUSE_LAST,
};

#endif	// #ifndef INCLUDED_KEYNAME
