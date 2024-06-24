#pragma once
#include <cstdint>
#include <vector>
#include <set>

#include "../Components/Component.hpp"
#include "../Components/IDs/ComponentIDs.hpp"

#include "../Events/Event.hpp"
#include "../Events/IDs/EventIDs.hpp"

#include "../TypeDefinitions.hpp"

struct Entity {
	Entity(EntityID id, EntityUpdateType _updateType) : ID(id), updateType(_updateType){};

	EntityUpdateType updateType;

	EntityID ID;

	// vector of component types that the entity has,
	// since sets are automatically sorted, iterating from 0-N in the componentTypesList
	// will always iterate according to the order of the "ComponentType" enum
	std::set<Components::ComponentTypeID> componentTypesList{};
	// vector of component types that have systems that the entity has
	std::set<Components::ComponentTypeID> componentTypesWithSystemsList;
	// vector of events types the entity has
	std::set<EntityEvents::EventTypeID> eventTypesList{};
};
