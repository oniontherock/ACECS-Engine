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

	LevelGrid<BaseLevel>::levelGet(level)->entityIdAdd(entityId);

	return entityId;
}
EntityId EntityManager::entityCreate(LevelCoordinate levelX, LevelCoordinate levelY, LevelCoordinate levelZ, EntityUpdateType updateType) {
	return entityCreate(LevelPosition(levelX, levelY, levelZ), updateType);
}

Entity& EntityManager::entityGet(EntityId entityId) {
	return entitiesVector[entityId];
}

void EntityManager::entityTerminate(EntityId entityID) {

	// move the entityId to a temporary variable
	Entity temp;
	temp.entityBecomeOther(entitiesVector[entityID]);
	// move the last entity in the entitiesVector to the position of the 
	entitiesVector[entityID].entityBecomeOther(entitiesVector[uint16_t(entityCount - 1)]);

	temp.terminate();
	
	LevelGrid<BaseLevel>::levelGet(temp.levelId)->entityIdRemove(temp.Id);

	entityCount--;
}
void EntityManager::entitiesAllDelete() {
	for (uint16_t i = 0; i < entityCount; i++) {
		entitiesVector[i].terminate();
	}
}