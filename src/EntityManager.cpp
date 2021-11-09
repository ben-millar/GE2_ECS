#include "EntityManager.h"

EntityManager::EntityManager()
{
	for (Entity e = 0U; e < MAX_ENTITIES; ++e)
		m_availableEntities.push(e);
}

///////////////////////////////////////////////////////////////

Entity EntityManager::createEntity()
{
	assert(m_availableEntities.size() && "Too many entities (MAX: 255)");

	Entity id = m_availableEntities.front();
	m_availableEntities.pop();

	return id;
}

///////////////////////////////////////////////////////////////

void EntityManager::destroyEntity(Entity t_entity)
{
	m_availableEntities.push(t_entity);
}

///////////////////////////////////////////////////////////////

void EntityManager::setSignature(Entity t_entity, Signature t_signature)
{
	m_signatures[t_entity] = t_signature;
}

///////////////////////////////////////////////////////////////

Signature EntityManager::getSignature(Entity t_entity)
{
	return m_signatures[t_entity];
}
