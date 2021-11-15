#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "System.h"
#include "Clock.h"

class PhysicsSystem :
    public System
{
    void Update(Time t_dT);
};

#endif