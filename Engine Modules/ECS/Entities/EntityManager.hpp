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

	inline void entitiesUpdate() {
		for (uint32_t i = 0; i < entityCount; i++) {
			entities[i].entityUpdate();
		}
	}

	inline EntityID entityCreate(EntityUpdateType updateType = EntityUpdateType::Frame) {
		EntityID entityID = entityCount;


		entities[entityID].entityCreate(entityID, updateType);

		entityCount++;

		return entityID;
	}
	inline void entityTerminate(EntityID entityID) {
		entities[entityID].terminate();

		Entity temp;
		temp.entityCreateFromOther(entities[entityID]);

		entities[entityID].terminate();
		entities[entityID].entityCreateFromOther(entities[uint16_t(entityCount - 1)]);

		entities[uint16_t(entityCount - 1)].terminate();
		entities[uint16_t(entityCount - 1)].entityCreateFromOther(temp);

		temp.terminate();

		entityCount--;
	}
	inline void entitiesAllDelete() {
		for (uint16_t i = 0; i < entityCount; i++) {
			entities[i].terminate();
		}
	}
};
