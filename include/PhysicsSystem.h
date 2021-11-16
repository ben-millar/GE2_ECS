#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <Coordinator.h>
#include <Clock.h>

class PhysicsSystem :
    public System
{
public:
    void update(Time t_dT);
};

#endif