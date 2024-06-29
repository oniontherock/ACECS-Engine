#pragma once
#include <unordered_set>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Entity.hpp"

#include "../TypeDefinitions.hpp"

namespace EntityManager {

	inline std::vector<Entity> entities = std::vector<Entity>(MAX_ENTITIES);

	inline uint32_t entityCount = 0;

	inline void updateEntities() {
		for (uint32_t i = 0; i < entityCount; i++) {
			entities[i].update();
		}
	}

	inline EntityID createEntity(EntityUpdateType updateType = EntityUpdateType::Frame) {
		EntityID entityID = entityCount;

		Entity entity = Entity(entityID, updateType);

		entities[entityID] = entity;

		entityCount++;

		return entityID;
	}
	inline void deleteEntity(EntityID entityID) {
		entities[entityID].clear();
		std::swap(entities[entityID], entities[entityCount - 1]);
		entityCount--;
	}
};
