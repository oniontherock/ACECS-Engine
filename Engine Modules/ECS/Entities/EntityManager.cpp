#include "EntityManager.hpp"

std::vector<Entity> EntityManager::entitiesVector = std::vector<Entity>(MAX_ENTITIES);

uint32_t EntityManager::entityCount = 0;

void EntityManager::entitiesUpdate() {
	for (uint32_t i = 0; i < entityCount; i++) {
		entitiesVector[i].entityUpdate();
	}
}
void EntityManager::entityUpdate(EntityId entityId) {
	entitiesVector[*entityId].entityUpdate();
}

EntityId EntityManager::entityCreate(EntityUpdateType updateType) {

	EntityId entityId = EntityId(new uint32_t(entityCount));

	Entity entity = Entity(entityId, updateType);

	entitiesVector[*entityId] = entity;

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
	return entitiesVector[*entityId];
}

void EntityManager::entityTerminate(EntityId entityId) {
	uint32_t lastInd = entityCount - 1;

	LevelGrid<BaseLevel>::levelGet(entitiesVector[*entityId].levelId)->entityIdRemove(entityId);
	//LevelGrid<BaseLevel>::levelGet(entitiesVector[lastInd].levelId)->entityIdRemove(entitiesVector[lastInd].Id);

	ConsoleHandler::consolePrintDebug("deleted");

	if (*entityId == lastInd) {
		entitiesVector[*entityId].terminate();
	}
	else {

		entitiesVector[*entityId].terminate();
		entitiesVector[*entityId] = entitiesVector[lastInd];
		//entitiesVector[lastInd].terminate();

		EntityId tempId = std::move(entityId);
		entitiesVector[*tempId].Id = std::move(entitiesVector[lastInd].Id);
		entitiesVector[lastInd].Id = std::move(tempId);
		*entitiesVector[lastInd].Id = UINT32_MAX;
	}

	entityCount--;
}
void EntityManager::entitiesAllDelete() {
	entitiesVector.clear();
}