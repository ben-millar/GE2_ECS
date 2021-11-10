#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <assert.h>
#include <Components.h>
#include <ComponentArray.h>

class ComponentManager
{
public:
	template<typename T>
	void RegisterComponent();

	template<typename T>
	Component getComponentType();

	template<typename T>
	void addComponent(Entity t_entity, T t_component);

	template<typename T>
	void removeComponent(Entity t_entity);

	template<typename T>
	T& getComponent(Entity t_entity);

	void entityDestroyed(Entity t_entity);


private:
	// Mapping of typeID str to component type
	std::unordered_map<const char*, Component> m_componentTypes;

	// Mapping of typeID str to component array
	std::unordered_map<const char*, void*> m_componentArrays;

	// The component ID to be assigned to the next registered component
	size_t m_nextComponentID = sizeof(Component);

	template<typename T>
	ComponentArray<T>* getComponentArray()
	{
		const char* typeName = typeid(T).name();
		assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered with component manager.");
		return (ComponentArray<T>*)m_componentArrays.at(typeName);
	}
};

template<typename T>
inline void ComponentManager::RegisterComponent()
{
	const char* typeName = typeid(T).name();
	assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Component already registered.");

	// Add component type to type map
	m_componentTypes.insert({ typeName, m_nextComponentID++ });

	// Allocate a new component array and add to the array map
	m_componentArrays.insert({ typeName, new ComponentArray<T>() });
}

///////////////////////////////////////////////////////////////

template<typename T>
inline Component ComponentManager::getComponentType()
{
	const char* typeName = typeid(T).name();
	assert(m_componentTypes.find(typeName) != m_componentTypes.end() && "Component not registered with component manager.");
	return m_componentTypes.at(typeName);
}

///////////////////////////////////////////////////////////////

template<typename T>
inline void ComponentManager::addComponent(Entity t_entity, T t_component)
{
	getComponentArray<T>()->insert(t_entity, t_component);
}

///////////////////////////////////////////////////////////////

template<typename T>
inline void ComponentManager::removeComponent(Entity t_entity)
{
	getComponentArray<T>()->remove(t_entity);
}

///////////////////////////////////////////////////////////////

template<typename T>
inline T& ComponentManager::getComponent(Entity t_entity)
{
	return getComponentArray<T>()->get(t_entity);
}

///////////////////////////////////////////////////////////////

inline void ComponentManager::entityDestroyed(Entity t_entity)
{
	for (auto const& pair : m_componentArrays)
	{
		auto const& component = pair.second;
		ComponentArray<Component>* p = (ComponentArray<Component>*)component;
		p->entityDestroyed(t_entity);
	}
}

#endif