#ifndef MINIMAL_PCH
# define MINIMAL_PCH 0
#endif

#include "config.h"	            // CONFIG_ENABLE_BOOST, CONFIG_ENABLE_PCH
#include "sysdep/compiler.h"    // MSC_VERSION, HAVE_PCH

// must come before any STL headers are included
#if MSC_VERSION
# ifdef NDEBUG	// release: disable all checks
#  define _HAS_ITERATOR_DEBUGGING 0
#  define _SECURE_SCL 0
# endif
#endif

// disable some common and annoying warnings
// (as soon as possible so that headers below are covered)
#include "pch/pch_warnings.h"

#if ICC_VERSION
#include <mathimf.h>	// (must come before <cmath> or <math.h> (replaces them))
double __cdecl abs(double x);	// not declared by mathimf
#endif


//
// headers made available everywhere for convenience
//

#include "posix/posix_types.h"	// (must come before any system headers because it fixes off_t)
#include "code_annotation.h"
#include "sysdep/arch.h"
#include "sysdep/os.h"
#include "sysdep/stl.h"
#include "lib_api.h"
#include "types.h"
#include "debug.h"
#include "lib.h"
#include "secure_crt.h"

#if CONFIG_ENABLE_BOOST
# include "pch/pch_boost.h"
#endif

#include <array>
#include <memory>
using std::shared_ptr;

// (must come after boost and common lib headers, but before re-enabling
// warnings to avoid boost spew)
#include "posix/posix.h"


//
// precompiled headers
//

// if PCHs are supported and enabled, we make an effort to include all
// system headers. otherwise, only a few central headers (e.g. types)
// are pulled in and source files must include all the system headers
// they use. this policy ensures good compile performance whether or not
// PCHs are being used.

#if CONFIG_ENABLE_PCH && HAVE_PCH

// anything placed here won't need to be compiled in each translation unit,
// but will cause a complete rebuild if they change.

#include "pch/pch_stdlib.h"

#endif // #if CONFIG_ENABLE_PCH && HAVE_PCH
