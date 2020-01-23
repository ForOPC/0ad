#ifndef INCLUDED_H_MGR
#define INCLUDED_H_MGR

// do not include from public header files!
// handle.h declares type Handle, and avoids making
// everything dependent on this (rather often updated) header.


#include <stdarg.h>		// type init routines get va_list of args

#ifndef INCLUDED_HANDLE
#include "handle.h"
#endif

#include "../file/vfs/vfs.h"

extern void h_mgr_init();
extern void h_mgr_shutdown();


// handle type (for 'type safety' - can't use a texture handle as a sound)

// registering extension for each module is bad - some may use many
// (e.g. texture - many formats).
// handle manager shouldn't know about handle types


/*
///xxx advantage of manual vtbl:
no boilerplate init, h_alloc calls ctor directly, make sure it fits in the memory slot
vtbl contains sizeof resource data, and name!
but- has to handle variable params, a bit ugly
*/

// 'manual vtbl' type id
// handles have a type, to prevent using e.g. texture handles as a sound.
//
// alternatives:
// - enum of all handle types (smaller, have to pass all methods to h_alloc)
// - class (difficult to compare type, handle manager needs to know of all users)
//
// checked in h_alloc:
// - user_size must fit in what the handle manager provides
// - name must not be 0
//
// init: user data is initially zeroed
// dtor: user data is zeroed afterwards
// reload: if this resource type is opened by another resource's reload,
// our reload routine MUST check if already opened! This is relevant when
// a file is reloaded: if e.g. a sound object opens a file, the handle
// manager calls the reload routines for the 2 handles in unspecified order.
// ensuring the order would require a tag field that can't overflow -
// not really guaranteed with 32-bit handles. it'd also be more work
// to sort the handles by creation time, or account for several layers of
// dependencies.
struct H_VTbl
{
	void (*init)(void* user, va_list);
	Status (*reload)(void* user, const PIVFS& vfs, const VfsPath& pathname, Handle);
	void (*dtor)(void* user);
	Status (*validate)(const void* user);
	Status (*to_string)(const void* user, wchar_t* buf);
	size_t user_size;
	const wchar_t* name;
};

typedef H_VTbl* H_Type;

#define H_TYPE_DEFINE(type)\
	/* forward decls */\
	static void type##_init(type*, va_list);\
	static Status type##_reload(type*, const PIVFS&, const VfsPath&, Handle);\
	static void type##_dtor(type*);\
	static Status type##_validate(const type*);\
	static Status type##_to_string(const type*, wchar_t* buf);\
	static H_VTbl V_##type =\
	{\
		(void (*)(void*, va_list))type##_init,\
		(Status (*)(void*, const PIVFS&, const VfsPath&, Handle))type##_reload,\
		(void (*)(void*))type##_dtor,\
		(Status (*)(const void*))type##_validate,\
		(Status (*)(const void*, wchar_t*))type##_to_string,\
		sizeof(type),	/* control block size */\
		WIDEN(#type)			/* name */\
	};\
	static H_Type H_##type = &V_##type

	// note: we cast to void* pointers so the functions can be declared to
	// take the control block pointers, instead of requiring a cast in each.
	// the forward decls ensure the function signatures are correct.


// convenience macro for h_user_data:
// casts its return value to the control block type.
// use if H_DEREF's returning a negative error code isn't acceptable.
#define H_USER_DATA(h, type) (type*)h_user_data(h, H_##type)

// even more convenient wrapper for h_user_data:
// declares a pointer (<var>), assigns it H_USER_DATA, and has
// the user's function return a negative error code on failure.
//
// note: don't use STMT - var decl must be visible to "caller"
#define H_DEREF(h, type, var)\
	/* h already indicates an error - return immediately to pass back*/\
	/* that specific error, rather than only ERR::INVALID_HANDLE*/\
	if(h < 0)\
		WARN_RETURN((Status)h);\
	type* const var = H_USER_DATA(h, type);\
	if(!var)\
		WARN_RETURN(ERR::INVALID_HANDLE);


// all functions check the passed tag (part of the handle) and type against
// the internal values. if they differ, an error is returned.




// h_alloc flags
enum
{
	// alias for RES_TEMP scope. the handle will not be kept open.
	RES_NO_CACHE = 0x01,

	// not cached, and will never reuse a previous instance
	RES_UNIQUE = RES_NO_CACHE|0x10,

	// object is requesting it never be reloaded (e.g. because it's not
	// backed by a file)
	RES_DISALLOW_RELOAD = 0x20
};

const size_t H_STRING_LEN = 256;



// allocate a new handle.
// if key is 0, or a (key, type) handle doesn't exist,
//   some free entry is used.
// otherwise, a handle to the existing object is returned,
//   and HDATA.size != 0.
//// user_size is checked to make sure the user data fits in the handle data space.
// dtor is associated with type and called when the object is freed.
// handle data is initialized to 0; optionally, a pointer to it is returned.
extern Handle h_alloc(H_Type type, const PIVFS& vfs, const VfsPath& pathname, size_t flags = 0, ...);
extern Status h_free(Handle& h, H_Type type);


// Forcibly frees all handles of a specified type.
void h_mgr_free_type(const H_Type type);


// find and return a handle by key (typically filename hash)
// currently O(log n).
//
// HACK: currently can't find RES_UNIQUE handles, because there
// may be multiple instances of them, breaking the lookup data structure.
extern Handle h_find(H_Type type, uintptr_t key);

// returns a void* pointer to the control block of the resource <h>,
// or 0 on error (i.e. h is invalid or of the wrong type).
// prefer using H_DEREF or H_USER_DATA.
extern void* h_user_data(Handle h, H_Type type);

extern VfsPath h_filename(Handle h);


extern Status h_reload(const PIVFS& vfs, const VfsPath& pathname);

// force the resource to be freed immediately, even if cached.
// tag is not checked - this allows the first Handle returned
// (whose tag will change after being 'freed', but remaining in memory)
// to later close the object.
// this is used when reinitializing the sound engine -
// at that point, all (cached) OpenAL resources must be freed.
extern Status h_force_free(Handle h, H_Type type);

// increment Handle <h>'s reference count.
// only meant to be used for objects that free a Handle in their dtor,
// so that they are copy-equivalent and can be stored in a STL container.
// do not use this to implement refcounting on top of the Handle scheme,
// e.g. loading a Handle once and then passing it around. instead, have each
// user load the resource; refcounting is done under the hood.
extern void h_add_ref(Handle h);

// retrieve the internal reference count or a negative error code.
// background: since h_alloc has no way of indicating whether it
// allocated a new handle or reused an existing one, counting references
// within resource control blocks is impossible. since that is sometimes
// necessary (always wrapping objects in Handles is excessive), we
// provide access to the internal reference count.
extern intptr_t h_get_refcnt(Handle h);

#endif	// #ifndef INCLUDED_H_MGR
