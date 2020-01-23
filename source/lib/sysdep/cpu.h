#ifndef INCLUDED_CPU
#define INCLUDED_CPU

#include "compiler.h"


namespace ERR
{
	const Status CPU_FEATURE_MISSING     = -130000;
	const Status CPU_UNKNOWN_OPCODE      = -130001;
	const Status CPU_UNKNOWN_VENDOR      = -130002;

}


//-----------------------------------------------------------------------------
// CPU detection

/**
 * @return string identifying the CPU (usually a cleaned-up version of the
 * brand string)
 **/
LIB_API const char* cpu_IdentifierString();


//-----------------------------------------------------------------------------
// lock-free support routines

/**
 * add a signed value to a variable without the possibility of interference
 * from other threads/CPUs.
 *
 * @return the previous value.
 **/
LIB_API intptr_t cpu_AtomicAdd(volatile intptr_t* location, intptr_t increment);

/**
 * atomic "compare and swap".
 *
 * @param location address of the word to compare and possibly overwrite
 * @param expected its expected value
 * @param newValue the value with which to replace it
 * @return false if the target word doesn't match the expected value,
 * otherwise true (also overwriting the contents of location)
 **/
LIB_API bool cpu_CAS(volatile intptr_t* location, intptr_t expected, intptr_t newValue);
LIB_API bool cpu_CAS64(volatile i64* location, i64 expected, i64 newValue);

/**
 * specialization of cpu_CAS for pointer types. this avoids error-prone
 * casting in user code.
 **/
template<typename T>
inline bool cpu_CAS(volatile T* location, T expected, T new_value)
{
	return cpu_CAS((volatile intptr_t*)location, (intptr_t)expected, (intptr_t)new_value);
}


LIB_API void cpu_Test();

/**
 * pause in spin-wait loops, as a performance optimisation.
 **/
inline void cpu_Pause()
{
#if MSC_VERSION && ARCH_X86_X64
	_mm_pause();
#elif GCC_VERSION && ARCH_X86_X64
	__asm__ __volatile__( "rep; nop" : : : "memory" );
#endif
}

#endif	// #ifndef INCLUDED_CPU
