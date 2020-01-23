#ifndef INCLUDED_SINGLETON
#define INCLUDED_SINGLETON

#include "../lib/debug.h"

template<typename T>
class Singleton
{
	static T* ms_singleton;

public:
	Singleton()
	{
		ENSURE( !ms_singleton );
		ms_singleton = static_cast<T*>(this);
	}

	~Singleton()
	{
		ENSURE( ms_singleton );
		ms_singleton = 0;
	}

	static T& GetSingleton()
	{
		ENSURE( ms_singleton );
		return *ms_singleton;
	}

	static T* GetSingletonPtr()
	{
		ENSURE( ms_singleton );
		return ms_singleton;
	}

	static bool IsInitialised()
	{
		return (ms_singleton != 0);
	}
};

template <typename T>
T* Singleton<T>::ms_singleton = 0;

#endif
