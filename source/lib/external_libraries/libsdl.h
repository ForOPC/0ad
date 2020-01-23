#ifndef INCLUDED_SDL
#define INCLUDED_SDL

#include "libsdl_fwd.h"

# include <SDL2/SDL.h>
# include <SDL2/SDL_thread.h>
// # include "SDL_thread.h"

#if !SDL_VERSION_ATLEAST(2,0,2)
#error You are using an old libsdl release. At least libsdl2 >= 2.0.2 is required.
#endif

// if the compiler doesn't support inlining, this header will pull
// in static bswap routines. doesn't matter - modern compilers
// will strip them if unused, and this is more convenient than
// another header that toggles between wsdl and SDL_endian.h.
# include <SDL2/SDL_endian.h>
//# include "SDL_endian.h"

# if MSC_VERSION
#  pragma comment(lib, "SDL2")
#  pragma comment(lib, "SDL2main")
# endif

// complete definition of our forward-declared SDL_Event (see sdl_fwd.h)
struct SDL_Event_
{
	SDL_Event ev;
};

#endif // INCLUDED_SDL
