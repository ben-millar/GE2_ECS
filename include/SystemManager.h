#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <assert.h>
#include <unordered_map>

#include <Components.h>
#include <System.h>

class SystemManager
{
public:
	template<typename T>
	T* registerSystem();

	template<typename T>
	void setSignature(Signature t_signature);

	void entityDestroyed(Entity t_entity);

	void entitySignatureChanged(Entity t_entity, Signature t_entitySignature);

private:
	// Map typeID string to a bitfield signature
	std::unordered_map<const char*, Signature> m_signatures{};

	// Map typeID string to a system*
	std::unordered_map<const char*, System*> m_systems{};
};

////////////////////////////////////////////////////////////

template<typename T>
inline T* SystemManager::registerSystem()
{
	const char* typeName = typeid(T).name();
	assert(m_systems.find(typeName) == m_systems.end() && ("System already registered."));

	auto sys = new T();
	m_systems[typeName] = sys;
	return sys;
}

////////////////////////////////////////////////////////////

template<typename T>
inline void SystemManager::setSignature(Signature t_signature)
{
	const char* typeName = typeid(T).name();
	assert(m_systems.find(typeName) != m_systems.end() && ("No system of type has been registered."));

	m_signatures[typeName] = t_signature;
}

////////////////////////////////////////////////////////////

inline void SystemManager::entityDestroyed(Entity t_entity)
{
	// Loop through systems, and erase entity from each (if exists)
	for (auto const& pair : m_systems)
		pair.second->m_entities.erase(t_entity);
}

////////////////////////////////////////////////////////////

inline void SystemManager::entitySignatureChanged(Entity t_entity, Signature t_entitySignature)
{
	const char* type;
	System* system;

	for (auto const& pair : m_systems)
	{
		std::tie(type, system) = pair;
		auto const& systemSignature = m_signatures[type];

		// Bitwise comparison of std::bitset signatures
		if ((t_entitySignature & systemSignature) == systemSignature)
			system->m_entities.insert(t_entity); // Signature still matches, insert updated entity into system
		else
			system->m_entities.erase(t_entity); // Signature no longer matches, remove entity from system
	}
}

#endif