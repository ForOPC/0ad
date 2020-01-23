#if OS_WIN
# include "../sysdep/os/win/wposix/wpthread.h"
#else
# include <pthread.h>
# include <semaphore.h>
#endif

#include "../posix/posix_errno.h"	// for user convenience
