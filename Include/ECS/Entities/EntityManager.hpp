#pragma once
#include <unordered_set>
#include <string>
#include <functional>
#include <set>
#include <unordered_map>
#include <algorithm>

#include "../Components/IDs/ComponentIDs.hpp"
#include "../Components/IDs/ComponentIDAllocator.hpp"

#include "Entity.hpp"

#include "../Systems/SystemManager.hpp"

#include "../TypeDefinitions.hpp"

namespace EntityManager {

	inline std::unordered_map<EntityID, Entity*> entities{};

	inline uint16_t entityCount = 0;
	inline std::set<EntityID> availableIDs{ 0 };

	inline EntityID getAvailableID() {

		EntityID lowestAvailableID = *std::min_element(availableIDs.begin(), availableIDs.end());

		return lowestAvailableID;
	}

	inline void runComponents(EntityID entityID) {
		for (Components::ComponentTypeID curComponentType : entities[entityID]->componentTypesWithSystemsList) {
			SystemManager::callSystem(entityID, curComponentType);
		}

		entities[entityID]->eventTypesList.clear();
	}

	inline void updateEntities() {
		auto it = entities.begin();

		std::for_each(
			entities.begin(), entities.end(),
			[](std::pair<EntityID, Entity*> pair) {
				runComponents(pair.second->ID);
			}
		);
	}

	inline EntityID createEntity(EntityUpdateType updateType) {


		Entity* entity = new Entity(getAvailableID(), updateType);

		EntityID entityID = getAvailableID();

		availableIDs.erase(entityID);
		entities.insert({ entityID, entity });
		availableIDs.insert(EntityID(entities.size()));

		return entityID;
	}
	inline void deleteEntity(EntityID entityID) {
		delete entities[entityID];
		entities.erase(entityID);
		availableIDs.insert(entityID);
	}
};
