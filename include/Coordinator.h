#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <EntityManager.h>
#include <ComponentManager.h>
#include <SystemManager.h>

class Coordinator
{
public:

	static Coordinator* getInstance()
	{
		static Coordinator instance;
		return &instance;
	}

	Coordinator(Coordinator const&) = delete;
	void operator=(Coordinator const&) = delete;

	void init();

	// Entity
	Entity createEntity();

	void destroyEntity(Entity t_entity);

	// Component
	template<typename T>
	void registerComponent();

	template<typename T>
	void addComponent(Entity t_entity, T t_component);

	template<typename T>
	void removeComponent(Entity t_entity);

	template<typename T>
	T& getComponent(Entity t_entity);

	template<typename T>
	Component getComponentType();

	// System
	template<typename T>
	T* registerSystem();

	template<typename T>
	void setSystemSignature(Signature t_signature);

private:
	Coordinator();

	EntityManager* m_entityManager;
	ComponentManager* m_componentManager;
	SystemManager* m_systemManager;
};

///////////////////////////////////////////////////////////////

inline void Coordinator::init()
{
	m_entityManager = EntityManager::getInstance();
	m_componentManager = new ComponentManager();
	m_systemManager = new SystemManager();
}

///////////////////////////////////////////////////////////////

inline Entity Coordinator::createEntity()
{
	return m_entityManager->createEntity();
}

///////////////////////////////////////////////////////////////

void Coordinator::destroyEntity(Entity t_entity)
{
	m_entityManager->destroyEntity(t_entity);
	m_componentManager->entityDestroyed(t_entity);
	m_systemManager->entityDestroyed(t_entity);
}

///////////////////////////////////////////////////////////////

template<typename T>
inline void Coordinator::registerComponent()
{
	m_componentManager->registerComponent<T>();
}

///////////////////////////////////////////////////////////////

template<typename T>
inline void Coordinator::addComponent(Entity t_entity, T t_component)
{
	// Add new component to our entity
	m_componentManager->addComponent<T>(t_entity, t_component);

	// Get original signature
	Signature signature = m_entityManager->getSignature(t_entity);

	// Set new component flag
	signature.set(m_componentManager->getComponentType<T>(), true);

	// Reassign updated signature
	m_entityManager->setSignature(entity, signature);

	// Inform the system manager so systems can subscribe/unsub to entity
	m_systemManager->entitySignatureChanged(entity, signature);
}

///////////////////////////////////////////////////////////////

template<typename T>
inline void Coordinator::removeComponent(Entity t_entity)
{
	m_componentManager->removeComponent<T>(entity);

	// Get original signature
	Signature signature = m_entityManager->getSignature(t_entity);

	// Unset removed component flag
	signature.set(m_componentManager->getComponentType<T>(), false);

	// Reassign updated signature
	m_entityManager->setSignature(entity, signature);

	// Inform the system manager so systems can subscribe/unsub to entity
	m_systemManager->entitySignatureChanged(entity, signature);
}

///////////////////////////////////////////////////////////////

template<typename T>
inline T& Coordinator::getComponent(Entity t_entity)
{
	return m_componentManager->getComponent<T>(t_entity);
}

///////////////////////////////////////////////////////////////

template<typename T>
inline Component Coordinator::getComponentType()
{
	return m_componentManager->getComponentType<T>();
}

///////////////////////////////////////////////////////////////

template<typename T>
inline T* Coordinator::registerSystem()
{
	return m_systemManager->registerSystem<T>();
}

///////////////////////////////////////////////////////////////

template<typename T>
inline void Coordinator::setSystemSignature(Signature t_signature)
{
	m_systemManager->setSignature<T>(t_signature);
}

#endif