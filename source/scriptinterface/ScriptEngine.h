#ifndef INCLUDED_SCRIPTENGINE
#define INCLUDED_SCRIPTENGINE

#include "ScriptTypes.h"
#include "../ps/Singleton.h"

/**
 * A class using the RAII (Resource Acquisition Is Initialization) idiom to manage initialization
 * and shutdown of the SpiderMonkey script engine. It also keeps a count of active script runtimes
 * in order to validate the following constraints:
 *  1. JS_Init must be called before any ScriptRuntimes are initialized
 *  2. JS_Shutdown must be called after all ScriptRuntimes have been destroyed
 */

class ScriptEngine : public Singleton<ScriptEngine>
{
public:
	ScriptEngine()
	{
		ENSURE(m_Runtimes.size() == 0 && "JS_Init must be called before any runtimes are created!");
		JS_Init();
	}

	~ScriptEngine()
	{
		ENSURE(m_Runtimes.size() == 0 && "All runtimes must be destroyed before calling JS_ShutDown!");
		JS_ShutDown();
	}

	void RegisterRuntime(const JSRuntime* rt) { m_Runtimes.push_back(rt); }
	void UnRegisterRuntime(const JSRuntime* rt) { m_Runtimes.remove(rt); }

private:

	std::list<const JSRuntime*> m_Runtimes;
};

#endif // INCLUDED_SCRIPTENGINE
