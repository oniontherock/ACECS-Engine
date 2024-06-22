#pragma once
#include <cstdint>


enum class EntityUpdateType : uint8_t {
	Never, // the entity is never updated by the entity updater, the entity can still be updated by external sources
	Frame, // the entity is updated every frame by the entity updater
};

typedef uint32_t EntityID;

constexpr uint16_t MAX_COMPONENT_TYPES = 32;
constexpr uint16_t MAX_EVENT_TYPES = 32;
