#ifndef INCLUDED_COMPONENTS
#define INCLUDED_COMPONENTS

// Defaults for TypeList.h macros
#define MESSAGE(name)
#define INTERFACE(name)
#define COMPONENT(name)

#undef MESSAGE
#define MESSAGE(name) MT_##name,
enum EMessageTypeId
{
	MT__Invalid = 0,
#include "../TypeList.h"
	MT__LastNative
};
#undef MESSAGE
#define MESSAGE(name)

#undef INTERFACE
#define INTERFACE(name) IID_##name,
enum EInterfaceId
{
	IID__Invalid = 0,
#include "../TypeList.h"
	IID__LastNative
};
#undef INTERFACE
#define INTERFACE(name)

#undef COMPONENT
#define COMPONENT(name) CID_##name,
enum EComponentTypeId
{
	CID__Invalid = 0,
#include "../TypeList.h"
	CID__LastNative
};
#undef COMPONENT
#define COMPONENT(name)

#undef MESSAGE
#undef INTERFACE
#undef COMPONENT

#endif // INCLUDED_COMPONENTS
