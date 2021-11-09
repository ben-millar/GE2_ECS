#ifndef ENTITY_H
#define ENTITY_H

#include <limits>
#include <stdint.h>

// Entity ID
using Entity = uint8_t;
const uint8_t MAX_ENTITIES = std::numeric_limits<uint8_t>::max();

#endif