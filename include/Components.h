#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <bitset>
#include <limits>
#include <stdint.h>

#include <Vector2.h>

using Component = uint8_t;
const uint8_t MAX_COMPONENTS = std::numeric_limits<uint8_t>::max();

using Signature = std::bitset<MAX_COMPONENTS>;

struct Gravity
{
	Vector2 force;
};

struct RigidBody
{
	Vector2 velocity;
	Vector2 acceleration;
};

struct Transform
{
	Vector2 position;
	Vector2 rotation;
	Vector2 scale;
};

#endif