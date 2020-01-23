#ifndef INCLUDED_COMPONENT
#define INCLUDED_COMPONENT

#include "../system/CmpPtr.h"
#include "../system/Components.h"
#include "../system/ComponentManager.h"
#include "../system/IComponent.h"
#include "../system/ParamNode.h"
#include "../system/SimContext.h"
#include "../serialization/ISerializer.h"
#include "../serialization/IDeserializer.h"

#define REGISTER_COMPONENT_TYPE(cname) \
	void RegisterComponentType_##cname(CComponentManager& mgr) \
	{ \
		mgr.RegisterComponentType(CCmp##cname::GetInterfaceId(), CID_##cname, CCmp##cname::Allocate, CCmp##cname::Deallocate, #cname, CCmp##cname::GetSchema()); \
		CCmp##cname::ClassInit(mgr); \
	}

#define REGISTER_COMPONENT_SCRIPT_WRAPPER(cname) \
	void RegisterComponentType_##cname(CComponentManager& mgr) \
	{ \
		mgr.RegisterComponentTypeScriptWrapper(CCmp##cname::GetInterfaceId(), CID_##cname, CCmp##cname::Allocate, CCmp##cname::Deallocate, #cname, CCmp##cname::GetSchema()); \
		CCmp##cname::ClassInit(mgr); \
	}

#define DEFAULT_COMPONENT_ALLOCATOR(cname) \
	static IComponent* Allocate(const ScriptInterface&, JS::HandleValue) { return new CCmp##cname(); } \
	static void Deallocate(IComponent* cmp) { delete static_cast<CCmp##cname*> (cmp); } \
	virtual int GetComponentTypeId() const \
	{ \
		return CID_##cname; \
	}

#define DEFAULT_SCRIPT_WRAPPER(cname) \
	static void ClassInit(CComponentManager& UNUSED(componentManager)) { } \
	static IComponent* Allocate(const ScriptInterface& scriptInterface, JS::HandleValue instance) \
	{ \
		return new CCmp##cname(scriptInterface, instance); \
	} \
	static void Deallocate(IComponent* cmp) \
	{ \
		delete static_cast<CCmp##cname*> (cmp); \
	} \
	CCmp##cname(const ScriptInterface& scriptInterface, JS::HandleValue instance) : m_Script(scriptInterface, instance) { } \
	static std::string GetSchema() \
	{ \
		return "<a:component type='script-wrapper'/><empty/>"; \
	} \
	virtual void Init(const CParamNode& paramNode) \
	{ \
		m_Script.Init(paramNode, GetEntityId()); \
	} \
	virtual void Deinit() \
	{ \
		m_Script.Deinit(); \
	} \
	virtual void HandleMessage(const CMessage& msg, bool global) \
	{ \
		m_Script.HandleMessage(msg, global); \
	} \
	virtual void Serialize(ISerializer& serialize) \
	{ \
		m_Script.Serialize(serialize); \
	} \
	virtual void Deserialize(const CParamNode& paramNode, IDeserializer& deserialize) \
	{ \
		m_Script.Deserialize(paramNode, deserialize, GetEntityId()); \
	} \
	virtual JS::Value GetJSInstance() const \
	{ \
		return m_Script.GetInstance(); \
	} \
	virtual int GetComponentTypeId() const \
	{ \
		return CID_##cname; \
	} \
	private: \
		CComponentTypeScript m_Script; \
	public:

#define DEFAULT_MOCK_COMPONENT() \
	virtual int GetComponentTypeId() const \
	{ \
		return -1; \
	} \
	virtual void Init(const CParamNode& UNUSED(paramNode)) \
	{ \
	} \
	virtual void Deinit() \
	{ \
	} \
	virtual void Serialize(ISerializer& UNUSED(serialize)) \
	{ \
	} \
	virtual void Deserialize(const CParamNode& UNUSED(paramNode), IDeserializer& UNUSED(deserialize)) \
	{ \
	} \

#endif // INCLUDED_COMPONENT
