#ifndef INCLUDED_POSIX_AIO
#define INCLUDED_POSIX_AIO

// despite the comment in wposix.h about not using Windows headers for
// POSIX declarations, this one is harmless (no incompatible declarations)
// and can safely be used on Windows as well.
#include <fcntl.h>

#if OS_WIN
# include "../sysdep/os/win/wposix/waio.h"
#elif OS_ANDROID || OS_OPENBSD
// Android doesn't provide aio.h. We don't actually use aio on Linuxes (see
// CONFIG2_FILE_ENABLE_AIO) but we use its symbols and structs, so define
// them here
# if OS_OPENBSD
// OpenBSD 5.1 (latest version at time of writing) has no struct sigevent defined,
// so we do this here.
struct sigevent
{
	int sigev_notify;
	int sigev_signo;
	union sigval sigev_value;
	void (*sigev_notify_function)(union sigval);
	pthread_attr_t *sigev_notify_attributes;
};
# endif
# define LIO_READ 0
# define LIO_WRITE 1
# define LIO_NOP 2
struct aiocb
{
	int aio_fildes;
	off_t aio_offset;
	volatile void* aio_buf;
	size_t aio_nbytes;
	int aio_reqprio;
	struct sigevent aio_sigevent;
	int aio_lio_opcode;
};
#else
# include <aio.h>
#endif

#include "posix_errno.h"	// for user convenience

#endif	// #ifndef INCLUDED_POSIX_AIO
