#include "PhysicsSystem.h"
#include "..\include\PhysicsSystem.h"

void PhysicsSystem::Update(Time t_dT)
{
	for (auto const& entity : m_entities)
	{
		auto& rb = Coordinator::getInstance()->getComponent<RigidBody>(entity);
		auto& transform = Coordinator::getInstance()->getComponent<Transform>(entity);
		auto& gravity = Coordinator::getInstance()->getComponent<Gravity>(entity);

		transform.position += rb.velocity * t_dT.asSeconds();
		rb.velocity += gravity.force * t_dT.asSeconds();
	}
}
