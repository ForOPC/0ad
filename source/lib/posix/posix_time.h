#if OS_WIN
# include "../sysdep/os/win/wposix/wtime.h"
#else
# include <sys/time.h>
#endif

#include "posix_errno.h"	// for user convenience
