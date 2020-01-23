#ifndef INCLUDED_POSIX_TYPES
#define INCLUDED_POSIX_TYPES

// this header defines e.g. ssize_t and int8_t without pulling in all
// POSIX declarations.
// included from lib/types.h in place of posix.h; this helps avoid conflicts
// due to incompatible winsock definitions.

#include "../sysdep/os.h"	// OS_WIN

// (must come before any system headers because it fixes off_t)
#if OS_WIN
# include "../sysdep/os/win/wposix/wposix_types.h"
#else

// unix/linux/glibc/gcc says that this macro has to be defined when including
// stdint.h from C++ for stdint.h to define SIZE_MAX and friends
# ifndef __STDC_LIMIT_MACROS
#  define __STDC_LIMIT_MACROS
# endif

# include <math.h>
# include <wchar.h>
# include <sys/types.h>
# include <stddef.h>
# include <limits.h>
# include <stdint.h>

// but sometimes it still doesn't get defined, so define it ourselves
# ifndef SIZE_MAX
#  define SIZE_MAX ((size_t)-1)
# endif

# include <unistd.h>

#endif	// #if !OS_WIN

#endif	// #ifndef INCLUDED_POSIX_TYPES
