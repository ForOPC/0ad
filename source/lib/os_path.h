#ifndef INCLUDED_OS_PATH
#define INCLUDED_OS_PATH

#include "path.h"

// rationale:
// users are responsible for ensuring the path doesn't contain any forbidden
// characters (including any code points < 0x00 or >= 0x100 on anything but Windows)
typedef Path OsPath;

#if OS_WIN

static inline const Path::String& OsString(const OsPath& path)
{
	return path.string();
}

#else

static inline std::string OsString(const OsPath& path)
{
	const Path::String& wstring = path.string();
	std::string string(wstring.length(), '\0');
	for(size_t i = 0; i < wstring.length(); i++)
	{
		ENSURE((unsigned)wstring[i] <= (unsigned)UCHAR_MAX);
		string[i] = (char)wstring[i];
	}
	return string;
}
#endif


#endif	// #ifndef INCLUDED_OS_PATH
