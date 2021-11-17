#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <Debug.h>

#include <EntityManager.h>
#include <ComponentManager.h>
#include <SystemManager.h>

class Coordinator
{
public:
	Coordinator() = default;

	static Coordinator* getInstance()
	{
		static Coordinator instance;
		return &instance;
	}

	Coordinator(Coordinator const&) = delete;
	void operator=(Coordinator const&) = delete;

	void init();

	//////////Entity//////////
	Entity createEntity();

	template<typename ...Args>
	Entity createEntity(Args... t_args);

	void destroyEntity(Entity t_entity);

	////////Component/////////
	template<typename T>
	void registerComponent();

	template<typename T, typename ...Args>
	void addComponent(Entity t_entity, T t_arg, Args... t_args);

	template<typename T>
	void addComponent(Entity t_entity, T t_component);

	template<typename T>
	void removeComponent(Entity t_entity);

	template<typename T>
	T& getComponent(Entity t_entity);

	template<typename T>
	Component getComponentType();

	//////////System//////////
	template<typename T>
	T* registerSystem();

	template<typename T>
	void setSystemSignature(Signature t_signature);

private:

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

template<typename ...Args>
inline Entity Coordinator::createEntity(Args... t_args)
{
	Entity e = createEntity();
	
	addComponent(e, t_args...);

	return e;
}

///////////////////////////////////////////////////////////////

inline void Coordinator::destroyEntity(Entity t_entity)
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

template<typename T, typename ...Args>
inline void Coordinator::addComponent(Entity t_entity, T t_arg, Args ... t_args)
{
	// Recursively call addComponent til we've run through our packed variadic args
	addComponent(t_entity, t_arg);
	addComponent(t_entity, t_args...);
}

///////////////////////////////////////////////////////////////

template<typename T>
inline void Coordinator::addComponent(Entity t_entity, T t_component)
{
	DEBUG_MSG("Adding component: " << typeid(T).name() << " to entity: " << (int)t_entity);

	// Add new component to our entity
	m_componentManager->addComponent<T>(t_entity, t_component);

	// Get original signature
	Signature signature = m_entityManager->getSignature(t_entity);

	// Set new component flag
	signature.set(m_componentManager->getComponentType<T>(), true);

	// Reassign updated signature
	m_entityManager->setSignature(t_entity, signature);

	// Inform the system manager so systems can subscribe/unsub to entity
	m_systemManager->entitySignatureChanged(t_entity, signature);
}

///////////////////////////////////////////////////////////////

template<typename T>
inline void Coordinator::removeComponent(Entity t_entity)
{
	m_componentManager->removeComponent<T>(t_entity);

	// Get original signature
	Signature signature = m_entityManager->getSignature(t_entity);

	// Unset removed component flag
	signature.set(m_componentManager->getComponentType<T>(), false);

	// Reassign updated signature
	m_entityManager->setSignature(t_entity, signature);

	// Inform the system manager so systems can subscribe/unsub to entity
	m_systemManager->entitySignatureChanged(t_entity, signature);
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