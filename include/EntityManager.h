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
	static EntityManager* getInstance()
	{
		static EntityManager instance;
		return &instance;
	}

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

#endif