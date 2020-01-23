#ifndef INCLUDED_OPENGL
#define INCLUDED_OPENGL

#include "../config2.h" // CONFIG2_GLES

#if OS_WIN
// wgl.h is a private header and should only be included from here.
// if this isn't defined, it'll complain.
#define WGL_HEADER_NEEDED
#include "../sysdep/os/win/wgl.h"
#endif

#if CONFIG2_GLES
# include <GLES2/gl2.h>
#elif OS_MACOSX || OS_MAC
# include <OpenGL/gl.h>
#else
# include <GL/gl.h>
#endif

// if gl.h provides real prototypes for 1.2 / 1.3 functions,
// exclude the corresponding function pointers in glext_funcs.h
#ifdef GL_VERSION_1_2
#define REAL_GL_1_2
#endif
#ifdef GL_VERSION_1_3
#define REAL_GL_1_3
#endif

// this must come after GL/gl.h include, so we can't combine the
// including GL/glext.h.
#undef GL_GLEXT_PROTOTYPES

#if CONFIG2_GLES
# include <GLES2/gl2ext.h>
#elif OS_MACOSX || OS_MAC
# include <OpenGL/glext.h>
#else
# include <GL/glext.h>
# if OS_WIN
#  include <GL/wglext.h>
# endif
#endif

#endif	// #ifndef INCLUDED_OPENGL
