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

	static std::vector<Entity> entities = std::vector<Entity>(MAX_ENTITIES);

	static uint32_t entityCount = 0;

	static void entitiesUpdate() {
		for (uint32_t i = 0; i < entityCount; i++) {
			entities[i].entityUpdate();
		}
	}

	static EntityID entityCreate(EntityUpdateType updateType = EntityUpdateType::Frame) {
		EntityID entityID = entityCount;

		Entity entity = Entity(entityID, updateType);

		entities[entityID] = entity;

		entityCount++;

		return entityID;
	}
	static void entityTerminate(EntityID entityID) {
		entities[entityID].terminate();
		std::swap(entities[entityID], entities[uint16_t(entityCount - 1)]);
		entityCount--;
	}
	static void entitiesAllDelete() {
		for (uint16_t i = 0; i < entityCount; i++) {
			entities[i].terminate();
		}
	}
};
