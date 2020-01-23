#include "../sysdep/compiler.h"	// ICC_VERSION
#include "../sysdep/arch.h"	// ARCH_IA32

#if MSC_VERSION
# pragma warning(disable:4710) // function not inlined
#if _MSC_VER > 1800
# pragma warning(disable:4626) // assignment operator was implicitly defined as deleted because a base class assignment operator is inaccessible or deleted
# pragma warning(disable:4625) // copy constructor was implicitly defined as deleted
# pragma warning(disable:4668) // 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
# pragma warning(disable:5027) // 'type': move assignment operator was implicitly defined as deleted
# pragma warning(disable:4365) // signed/unsigned mismatch
# pragma warning(disable:4619) // there is no warning for 'warning'
# pragma warning(disable:5031) // #pragma warning(pop): likely mismatch, popping warning state pushed in different file
# pragma warning(disable:5026) // 'type': move constructor was implicitly defined as deleted
# pragma warning(disable:4820) // incorrect padding
# pragma warning(disable:4514) // unreferenced inlined function has been removed
# pragma warning(disable:4571) // Informational: catch(...) semantics changed since Visual C++ 7.1; structured exceptions (SEH) are no longer caught
#endif
#endif
#if ICC_VERSION
# pragma warning(push)
# pragma warning(disable:82)	// storage class is not first
# pragma warning(disable:193)	// zero used for undefined preprocessing identifier
# pragma warning(disable:304)	// access control not specified
# pragma warning(disable:367)	// duplicate friend declaration
# pragma warning(disable:444)	// destructor for base class is not virtual
# pragma warning(disable:522)	// function redeclared inline after being called
# pragma warning(disable:811)	// exception specification for implicitly declared virtual function is incompatible with that of overridden function
# pragma warning(disable:1879)	// unimplemented pragma ignored
# pragma warning(disable:2270)	// the declaration of the copy assignment operator has been suppressed
# pragma warning(disable:2273)	// the declaration of the copy constructor has been suppressed
# if ARCH_IA32
#  pragma warning(disable:693)	// calling convention specified here is ignored
# endif
#endif
