#include "EntityManager.hpp"
#include "../../World/LevelGrid.hpp"


std::vector<Entity> EntityManager::entitiesVector = std::vector<Entity>(MAX_ENTITIES);
std::set<EntityId> EntityManager::entityIdsSet = std::set<EntityId>();

void EntityManager::entityIdsInitialize() {
	for (EntityId i = 0; i < MAX_ENTITIES; i++) {
		entityIdsSet.insert(i);
	}
}

void EntityManager::entityUpdate(EntityId entityId) {
	entitiesVector[entityId].entityUpdate();
}

void EntityManager::entityCreateWithId(EntityId id) {

	entityIdsSet.erase(id);

	entitiesVector[id] = Entity(id, EntityUpdateType::Frame);
}
EntityId EntityManager::entityCreate(EntityUpdateType updateType) {
	
	EntityId id = *entityIdsSet.begin();
	entityCreateWithId(id);

	entitiesVector[id].updateType = updateType;

	return entitiesVector[id].Id;
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

void EntityManager::entityTerminate(EntityId entityId) {

	LevelGrid<BaseLevel>::levelGet(entitiesVector[entityId].levelId)->entityIdRemove(entityId);

	entitiesVector[entityId].terminate();
	entityIdsSet.insert(entityId);
}
void EntityManager::entitiesAllDelete() {
	entitiesVector.clear();
}

