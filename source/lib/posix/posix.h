#ifndef INCLUDED_POSIX
#define INCLUDED_POSIX

#include <cmath>	// see isfinite comment below

#if OS_WIN
# include "../sysdep/os/win/wposix/wposix.h"
#endif

#include "posix_types.h"

// disabled to reduce dependencies. include them where needed.
//#include "lib/posix/posix_aio.h"
//#include "lib/posix/posix_dlfcn.h"
//#include "lib/posix/posix_filesystem.h"
//#include "lib/posix/posix_mman.h"
//#include "lib/posix/posix_pthread.h"
//#include "lib/posix/posix_time.h"
//#include "lib/posix/posix_utsname.h"


// note: the following need only be #defined (instead of defining a
// trampoline function) because the redefined functions are already
// declared by standard headers.

// provide C99 *snprintf functions if compiler doesn't already
// (MinGW does, VC7.1 doesn't).
#if MSC_VERSION
# define snprintf _snprintf
# define swprintf _snwprintf
# define vsnprintf _vsnprintf
# define vswprintf _vsnwprintf
#endif

// VC doesn't define str[n]casecmp
#if MSC_VERSION
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#define wcscasecmp _wcsicmp
#define wcsncasecmp _wcsnicmp
#endif

#if OS_MACOSX
# define EMULATE_WCSDUP 1
# define EMULATE_WCSCASECMP 1
#else
# define EMULATE_WCSDUP 0
# define EMULATE_WCSCASECMP 0
#endif

#if EMULATE_WCSDUP
extern wchar_t* wcsdup(const wchar_t* str);
#endif

#if EMULATE_WCSCASECMP
extern int wcscasecmp(const wchar_t* s1, const wchar_t* s2);
#endif

// Some systems have C99 support but in C++ they provide only std::isfinite
// and not isfinite. C99 specifies that isfinite is a macro, so we can use
// #ifndef and define it if it's not there already.
// We've included <cmath> above to make sure it defines that macro.
#ifndef isfinite
# if MSC_VERSION
#  define isfinite _finite
#  define isnan _isnan
# else
#  define isfinite std::isfinite
#  define isnan std::isnan
# endif
#endif

#endif	// #ifndef INCLUDED_POSIX
