#include "precompiled.h"
#include "lib.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "app_hooks.h"
#include "sysdep/sysdep.h"


//-----------------------------------------------------------------------------
// type conversion

// these avoid a common mistake in using >> (ANSI requires shift count be
// less than the bit width of the type).

u32 u64_hi(u64 x)
{
	return (u32)(x >> 32);
}

u32 u64_lo(u64 x)
{
	return (u32)(x & 0xFFFFFFFF);
}

u16 u32_hi(u32 x)
{
	return (u16)(x >> 16);
}

u16 u32_lo(u32 x)
{
	return (u16)(x & 0xFFFF);
}


u64 u64_from_u32(u32 hi, u32 lo)
{
	u64 x = (u64)hi;
	x <<= 32;
	x |= lo;
	return x;
}

u32 u32_from_u16(u16 hi, u16 lo)
{
	u32 x = (u32)hi;
	x <<= 16;
	x |= lo;
	return x;
}


// input in [0, 1); convert to u8 range
u8 u8_from_double(double in)
{
	if(!(0.0 <= in && in < 1.0))
	{
		DEBUG_WARN_ERR(ERR::LOGIC);	// clampf not in [0,1)
		return 255;
	}

	int l = (int)(in * 255.0);
	ENSURE((unsigned)l <= 255u);
	return (u8)l;
}

// input in [0, 1); convert to u16 range
u16 u16_from_double(double in)
{
	if(!(0.0 <= in && in < 1.0))
	{
		DEBUG_WARN_ERR(ERR::LOGIC);	// clampf not in [0,1)
		return 65535;
	}

	long l = (long)(in * 65535.0);
	ENSURE((unsigned long)l <= 65535u);
	return (u16)l;
}
