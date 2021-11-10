#ifndef SYSTEM_H
#define SYSTEM_H

#include <unordered_set>

#include <Entity.h>

class System
{
public:
	std::unordered_set<Entity> m_entities;
};

#endif