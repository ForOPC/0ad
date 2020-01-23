#ifndef INCLUDED_LIB_API
#define INCLUDED_LIB_API

#include "sysdep/compiler.h"

// note: EXTERN_C cannot be used because shared_ptr is often returned
// by value, which requires C++ linkage.

#ifdef LIB_STATIC_LINK
# define LIB_API
#else
# if MSC_VERSION
#  ifdef LIB_BUILD
#   define LIB_API __declspec(dllexport)
#  else
#   define LIB_API __declspec(dllimport)
#   ifdef NDEBUG
#    pragma comment(lib, "lowlevel.lib")
#   else
#    pragma comment(lib, "lowlevel_d.lib")
#   endif
#  endif
# elif GCC_VERSION
#  ifdef LIB_BUILD
#   define LIB_API __attribute__ ((visibility("default")))
#  else
#   define LIB_API
#  endif
# else
#  error "Don't know how to define LIB_API for this compiler"
# endif
#endif

#endif	// #ifndef INCLUDED_LIB_API
