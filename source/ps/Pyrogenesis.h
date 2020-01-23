#ifndef INCLUDED_PYROGENESIS
#define INCLUDED_PYROGENESIS

#include "../lib/os_path.h"

extern const char engine_version[];

extern void psBundleLogs(FILE* f); // set during InitVfs
extern void psSetLogDir(const OsPath& logDir);	// set during InitVfs
extern const OsPath& psLogDir();	// used by AppHooks and engine code when reporting errors

#endif
