#pragma once
#include <cstdint>


enum class EntityUpdateType : uint8_t {
	Never, // the entity is never updated by the entity updater, the entity can still be updated by external sources
	Frame, // the entity is updated every frame by the entity updater
};

typedef uint32_t EntityID;

#ifndef MAX_ENTITIES
#define MAX_ENTITIES 10000
#endif

#ifndef MAX_COMPONENT_TYPES
#define MAX_COMPONENT_TYPES 32
#endif

#ifndef MAX_EVENT_TYPES
#define MAX_EVENT_TYPES 32
#endif

