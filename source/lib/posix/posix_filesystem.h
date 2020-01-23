#include <fcntl.h>	// O_CREAT etc.

#if OS_WIN
# include "../sysdep/os/win/wposix/wfilesystem.h"
#else
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
#endif

#include "posix_errno.h"	// for user convenience
