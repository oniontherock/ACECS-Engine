#pragma once
#include <cstdint>


enum class EntityUpdateType : uint8_t {
	Never, // the entity is never updated by the entity updater, the entity can still be updated by external sources
	Frame, // the entity is updated every frame by the entity updater
};

typedef uint32_t EntityId;

extern uint32_t MAX_ENTITIES;
extern uint16_t MAX_COMPONENT_TYPES;
extern uint16_t MAX_EVENT_TYPES;
