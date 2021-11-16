#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <array>
#include <assert.h>
#include <queue>

#include <Components.h>
#include <Entity.h>

class EntityManager
{
public:
	static EntityManager* getInstance();

	EntityManager(EntityManager const&) = delete;
	void operator=(EntityManager const&) = delete;

	Entity createEntity();

	void destroyEntity(Entity t_entity);

	void setSignature(Entity t_entity, Signature t_signature);

	Signature getSignature(Entity t_entity);

private:
	EntityManager();

	std::queue<Entity> m_availableEntities;
	std::array<Signature, MAX_ENTITIES> m_signatures;
};

////////////////////////////////////////////////////////////

inline EntityManager::EntityManager()
{
	for (Entity e = 0U; e < MAX_ENTITIES; ++e)
		m_availableEntities.push(e);
}

////////////////////////////////////////////////////////////

inline EntityManager* EntityManager::getInstance()
{
	static EntityManager instance;
	return &instance;
}

////////////////////////////////////////////////////////////

inline Entity EntityManager::createEntity()
{
	assert(m_availableEntities.size() && "Too many entities (MAX: 255)");

	Entity id = m_availableEntities.front();
	m_availableEntities.pop();

	return id;
}

////////////////////////////////////////////////////////////

inline void EntityManager::destroyEntity(Entity t_entity)
{
	m_availableEntities.push(t_entity);
}

////////////////////////////////////////////////////////////

inline void EntityManager::setSignature(Entity t_entity, Signature t_signature)
{
	m_signatures[t_entity] = t_signature;
}

////////////////////////////////////////////////////////////

inline Signature EntityManager::getSignature(Entity t_entity)
{
	return m_signatures[t_entity];
}

#endif