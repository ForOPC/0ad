#ifndef INCLUDED_STL
#define INCLUDED_STL

#include "../config.h"
#include "compiler.h"
#include <cstdlib> // indirectly pull in bits/c++config.h on Linux, so __GLIBCXX__ is defined

// detect STL version
// .. Dinkumware
#if MSC_VERSION
# include <yvals.h>	// defines _CPPLIB_VER
#endif
#if defined(_CPPLIB_VER)
# define STL_DINKUMWARE _CPPLIB_VER
#else
# define STL_DINKUMWARE 0
#endif
// .. GCC
#if defined(__GLIBCPP__)
# define STL_GCC __GLIBCPP__
#elif defined(__GLIBCXX__)
# define STL_GCC __GLIBCXX__
#else
# define STL_GCC 0
#endif
// .. ICC
#if defined(__INTEL_CXXLIB_ICC)
# define STL_ICC __INTEL_CXXLIB_ICC
#else
# define STL_ICC 0
#endif


// disable (slow!) iterator checks in release builds (unless someone already defined this)
#if STL_DINKUMWARE && defined(NDEBUG) && !defined(_SECURE_SCL)
# define _SECURE_SCL 0
#endif


// pass "disable exceptions" setting on to the STL
#if CONFIG_DISABLE_EXCEPTIONS
# if STL_DINKUMWARE
#  define _HAS_EXCEPTIONS 0
# else
#  define STL_NO_EXCEPTIONS
# endif
#endif


// OS X - fix some stream template instantiations that break 10.5 compatibility on newer SDKs
#if OS_MACOSX
# include "os/osx/osx_stl_fixes.h"
#endif

#endif	// #ifndef INCLUDED_STL
