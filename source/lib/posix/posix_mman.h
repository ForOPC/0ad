#ifndef INCLUDED_POSIX_MMAN
#define INCLUDED_POSIX_MMAN

#if OS_WIN
# include "../sysdep/os/win/wposix/wmman.h"
#else
# include <sys/mman.h>
#endif

#include "posix_errno.h"	// for user convenience

#endif	// #ifndef INCLUDED_POSIX_MMAN
