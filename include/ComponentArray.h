#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H

#include <array>
#include <assert.h>
#include <unordered_map>

#include <Entity.h>

template<typename T>
class ComponentArray
{
public:
	void insert(Entity t_entity, T t_component);
	void remove(Entity t_entity);
	T& get(Entity t_entity);
	void entityDestroyed(Entity t_entity);

	// Overloaded [] get operator
	T operator[](Entity t_entity) const;

private:
	std::array<T, MAX_ENTITIES> m_componentArrays;

	std::unordered_map<Entity, size_t> m_entityToIndex;
	std::unordered_map<size_t, Entity> m_indexToEntity;

	size_t m_size;
};

///////////////////////////////////////////////////////////////

template<typename T>
inline void ComponentArray<T>::insert(Entity t_entity, T t_component)
{
	assert(m_entityToIndex.find(t_entity) == m_entityToIndex.end() && "Component added to same entity more than once.");

	m_entityToIndex[t_entity] = m_size;
	m_indexToEntity[m_size] = t_entity;
	m_componentArrays[m_size] = t_component;
	
	++m_size;
}

///////////////////////////////////////////////////////////////

template<typename T>
inline void ComponentArray<T>::remove(Entity t_entity)
{
	assert(m_entityToIndex.find(t_entity) != m_entityToIndex.end() && "Removing non-existent component.");

	size_t indexOfRemovedEntity = m_entityToIndex[t_entity];
	size_t indexOfLastElement = --m_size;

	// Copy last element into the gap created
	m_componentArrays[indexOfRemovedEntity] = m_componentArrays[indexOfLastElement];

	Entity entityOfLastElement = m_indexToEntity[indexOfLastElement];
	m_entityToIndex[entityOfLastElement] = indexOfRemovedEntity;
	m_indexToEntity[indexOfRemovedEntity] = entityOfLastElement;

	m_entityToIndex.erase(t_entity);
	m_indexToEntity.erase(m_size);
}

///////////////////////////////////////////////////////////////

template<typename T>
inline T& ComponentArray<T>::get(Entity t_entity)
{
	assert(m_entityToIndex.find(t_entity) != m_entityToIndex.end() && "Retrieving non-existent component.");

	return m_componentArrays[m_entityToIndex[t_entity]];
}

///////////////////////////////////////////////////////////////

template<typename T>
inline void ComponentArray<T>::entityDestroyed(Entity t_entity)
{
	if (m_entityToIndex.find(t_entity) != m_entityToIndex.end())
		remove(t_entity);
}

///////////////////////////////////////////////////////////////

template<typename T>
inline T ComponentArray<T>::operator[](Entity t_entity) const
{
	return get(t_entity);
}

#endif