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

	entitiesVector[entityId] = Entity(entityId, updateType);

	entityCount++;

	return entityId;
}
EntityId EntityManager::entityCreate(LevelPosition level, EntityUpdateType updateType) {

	EntityId entityId = entityCreate(updateType);

	entityAddToRoom(entityId, level);

	return entityId;
}
EntityId EntityManager::entityCreate(LevelCoordinate levelX, LevelCoordinate levelY, LevelCoordinate levelZ, EntityUpdateType updateType) {
	return entityCreate(LevelPosition(levelX, levelY, levelZ), updateType);
}
EntityId EntityManager::entityCreate(ComponentTemplateName templateName, EntityUpdateType updateType) {
	EntityId entityId = entityCreate(updateType);

	ComponentTemplateManager::componentTemplateApplyToEntity(templateName, entityGet(entityId));

	return entityId;
}
EntityId EntityManager::entityCreate(LevelPosition level, ComponentTemplateName templateName, EntityUpdateType updateType) {
	EntityId entityId = entityCreate(level, updateType);

	ComponentTemplateManager::componentTemplateApplyToEntity(templateName, entityGet(entityId));

	return entityId;
}

EntityId EntityManager::entityCreate(LevelCoordinate levelX, LevelCoordinate levelY, LevelCoordinate levelZ, ComponentTemplateName templateName,
	EntityUpdateType updateType) {
	return entityCreate(LevelPosition(levelX, levelY, levelZ), templateName, updateType);
}

void EntityManager::entityAddToRoom(EntityId entityId, LevelPosition level) {
	LevelGrid<BaseLevel>::levelGet(level)->entityIdAdd(entityId);

}
void EntityManager::entityAddToRoom(EntityId entityId, LevelCoordinate levelX, LevelCoordinate levelY, LevelCoordinate levelZ) {
	entityAddToRoom(entityId, LevelPosition(levelX, levelY, levelZ));
}

Entity& EntityManager::entityGet(EntityId entityId) {
	return entitiesVector[entityId];
}

void EntityManager::entityTerminate(EntityId entityID) {

	LevelGrid<BaseLevel>::levelGet(entitiesVector[entityID].levelId)->entityIdRemove(entitiesVector[entityID].Id);

	// move the last entity in the entitiesVector to the position of the entity we are terminating
	entitiesVector[entityID] = entitiesVector[uint16_t(entityCount - 1)];

	entityCount--;
}
void EntityManager::entitiesAllDelete() {
	entitiesVector.clear();
}