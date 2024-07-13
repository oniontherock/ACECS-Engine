#include "EntityManager.hpp"

std::vector<Entity> EntityManager::entities = std::vector<Entity>(MAX_ENTITIES);

uint32_t EntityManager::entityCount = 0;

void EntityManager::entitiesUpdate() {
	for (uint32_t i = 0; i < entityCount; i++) {
		entities[i].entityUpdate();
	}
}

EntityId EntityManager::entityCreate(EntityUpdateType updateType) {

	EntityId entityId = entityCount;

	entities[entityId].entityCreate(entityId, updateType);

	entityCount++;

	return entityId;
}

EntityId EntityManager::entityCreate(LevelPosition level, EntityUpdateType updateType) {

	EntityId entityId = entityCreate(updateType);

	GameWorld::levelGet(level)->entityIdAdd(entityId);

	return entityId;
}
EntityId EntityManager::entityCreate(LevelCoordinate levelX, LevelCoordinate levelY, LevelCoordinate levelZ, EntityUpdateType updateType) {
	return entityCreate(LevelPosition(levelX, levelY, levelZ), updateType);
}

void EntityManager::entityTerminate(EntityId entityID) {
	entities[entityID].terminate();

	Entity temp;
	temp.entityBecomeOther(entities[entityID]);

	entities[entityID].terminate();
	entities[entityID].entityBecomeOther(entities[uint16_t(entityCount - 1)]);

	entities[uint16_t(entityCount - 1)].terminate();
	entities[uint16_t(entityCount - 1)].entityBecomeOther(temp);

	temp.terminate();

	entityCount--;
}
void EntityManager::entitiesAllDelete() {
	for (uint16_t i = 0; i < entityCount; i++) {
		entities[i].terminate();
	}
}