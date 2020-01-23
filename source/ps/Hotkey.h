#ifndef INCLUDED_HOTKEY
#define INCLUDED_HOTKEY

/**
 * @file
 * Hotkey system.
 *
 * Hotkeys consist of a name (an arbitrary string), and a key mapping.
 * The names and mappings are loaded from the config system (any
 * config setting with the name prefix "hotkey.").
 * When a hotkey is pressed or released, SDL_HOTKEYDOWN and SDL_HOTKEYUP
 * events are triggered, with the hotkey name stored in ev.user.data1
 * as a const char*.
 */

#include "CStr.h"
#include "../lib/input.h"
#include "../lib/external_libraries/libsdl.h"	// see note below

// note: we need the real SDL header - it defines SDL_USEREVENT, which is
// required for our HOTKEY event type definition. this is OK since
// hotkey.h is not included from any headers.

const int SDL_HOTKEYDOWN = SDL_USEREVENT;
const int SDL_HOTKEYUP = SDL_USEREVENT + 1;

extern void LoadHotkeys();
extern void UnloadHotkeys();
extern InReaction HotkeyInputHandler(const SDL_Event_* ev);

extern bool HotkeyIsPressed(const CStr& keyname);

#endif // INCLUDED_HOTKEY
