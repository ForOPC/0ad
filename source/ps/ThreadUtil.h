#ifndef INCLUDED_THREADUTIL
#define INCLUDED_THREADUTIL

#include "../lib/posix/posix_pthread.h"

#ifdef DEBUG_LOCKS

#define LOCK_MUTEX(_mutex) STMT( \
	printf("pthread_mutex_lock: 1 %p [pid:%d]\n", _mutex, pthread_self()); \
	pthread_mutex_lock(_mutex); \
	printf("pthread_mutex_lock: 2 %p [pid:%d]\n", _mutex, pthread_self()) \
)
#define UNLOCK_MUTEX(_mutex) STMT( \
	pthread_mutex_unlock(_mutex); \
	printf("pthread_mutex_unlock: %p [pid:%d]\n", _mutex, pthread_self()) \
)

#else

#define LOCK_MUTEX(_mutex) pthread_mutex_lock(_mutex)
#define UNLOCK_MUTEX(_mutex) pthread_mutex_unlock(_mutex)

#endif

/**
 * A non-recursive mutual exclusion lock.
 */
class CMutex
{
	NONCOPYABLE(CMutex);

	friend class CScopeLock;

public:
	CMutex()
	{
		int ret = pthread_mutex_init(&m_Mutex, NULL);
		ENSURE(ret == 0);
	}

	~CMutex()
	{
		int ret = pthread_mutex_destroy(&m_Mutex);
		ENSURE(ret == 0);
	}

private:
	pthread_mutex_t m_Mutex;
};

/**
 * Locks a CMutex over this object's lifetime.
 * The mutexes are non-recursive - a single thread locking a mutex more than once
 * results in undefined behaviour.
 */
class CScopeLock
{
	NONCOPYABLE(CScopeLock);

public:
	CScopeLock(pthread_mutex_t* mutex) :
		m_Mutex(mutex)
	{
		LOCK_MUTEX(m_Mutex);
	}

	CScopeLock(CMutex& mutex) :
		m_Mutex(&mutex.m_Mutex)
	{
		LOCK_MUTEX(m_Mutex);
	}

	~CScopeLock()
	{
		UNLOCK_MUTEX(m_Mutex);
	}

private:
	pthread_mutex_t* m_Mutex;
};


namespace ThreadUtil
{

/**
 * Returns whether the current thread is the 'main' thread
 * (i.e. matches an earlier call to SetMainThread).
 */
bool IsMainThread();

/**
 * Set the current thread as the 'main' thread.
 * (This is called during engine initialisation.)
 */
void SetMainThread();

}

#endif // INCLUDED_THREADUTIL
