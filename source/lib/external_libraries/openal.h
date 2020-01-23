#ifndef INCLUDED_OPENAL
#define INCLUDED_OPENAL

#if OS_MACOSX
# include <OpenAL/al.h>
# include <OpenAL/alc.h>
#else
# include <AL/al.h>
# include <AL/alc.h>
#endif

// ALC strings (e.g. device and extension names) are typed differently
// between OpenAL specifications
#ifdef AL_VERSION_1_1
typedef ALCchar* alcString;
#else
typedef ALCubyte* alcString;
#endif

#if MSC_VERSION
# pragma comment(lib, "openal32.lib")
#endif

#endif	// #ifndef INCLUDED_OPENAL
