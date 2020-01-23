#include "precompiled.h"
#include "module_init.h"

#include "sysdep/cpu.h"	// cpu_CAS

// not yet initialized, or already shutdown
static const ModuleInitState UNINITIALIZED = 0;	// value documented in header
// running user callback - concurrent ModuleInit callers must spin
static const ModuleInitState BUSY = ERR::AGAIN;	// never returned
// init succeeded; allow shutdown
static const ModuleInitState INITIALIZED = INFO::SKIPPED;


Status ModuleInit(volatile ModuleInitState* initState, Status (*init)())
{
	for(;;)
	{
		if(cpu_CAS(initState, UNINITIALIZED, BUSY))
		{
			Status ret = init();
			*initState = (ret == INFO::OK)? INITIALIZED : ret;
			COMPILER_FENCE;
			return ret;
		}

		const ModuleInitState latchedInitState = *initState;
		if(latchedInitState == UNINITIALIZED || latchedInitState == BUSY)
		{
			cpu_Pause();
			continue;
		}

		ENSURE(latchedInitState == INITIALIZED || latchedInitState < 0);
		return (Status)latchedInitState;
	}
}


Status ModuleShutdown(volatile ModuleInitState* initState, void (*shutdown)())
{
	for(;;)
	{
		if(cpu_CAS(initState, INITIALIZED, BUSY))
		{
			shutdown();
			*initState = UNINITIALIZED;
			COMPILER_FENCE;
			return INFO::OK;
		}

		const ModuleInitState latchedInitState = *initState;
		if(latchedInitState == INITIALIZED || latchedInitState == BUSY)
		{
			cpu_Pause();
			continue;
		}

		if(latchedInitState == UNINITIALIZED)
			return INFO::SKIPPED;

		ENSURE(latchedInitState < 0);
		return (Status)latchedInitState;
	}
}
