#include "EntityManager.hpp"

std::vector<Entity> EntityManager::entitiesVector = std::vector<Entity>(MAX_ENTITIES);

uint32_t EntityManager::entityCount = 0;

void EntityManager::entitiesUpdate() {
	for (uint32_t i = 0; i < entityCount; i++) {
		entitiesVector[i].entityUpdate();
	}
}
void EntityManager::entityUpdate(EntityId entityId) {
	entitiesVector[entityId].entityUpdate();
}

EntityId EntityManager::entityCreate(EntityUpdateType updateType) {

	EntityId entityId = entityCount;

	entitiesVector[entityId].entityCreate(entityId, updateType);

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
	entitiesVector[entityID].terminate();

	Entity temp;
	temp.entityBecomeOther(entitiesVector[entityID]);

	entitiesVector[entityID].terminate();
	entitiesVector[entityID].entityBecomeOther(entitiesVector[uint16_t(entityCount - 1)]);

	entitiesVector[uint16_t(entityCount - 1)].terminate();
	entitiesVector[uint16_t(entityCount - 1)].entityBecomeOther(temp);

	temp.terminate();

	entityCount--;
}
void EntityManager::entitiesAllDelete() {
	for (uint16_t i = 0; i < entityCount; i++) {
		entitiesVector[i].terminate();
	}
}