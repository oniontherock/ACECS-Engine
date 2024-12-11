#include "EntityManager.hpp"
#include "../../World/LevelGrid.hpp"


std::vector<Entity> EntityManager::entitiesVector = std::vector<Entity>(MAX_ENTITIES);
std::set<EntityId> EntityManager::entityIdsSet = std::set<EntityId>();
std::set<EntityId> EntityManager::entitiesIntangible = std::set<EntityId>();
std::queue<EntityId> EntityManager::entitiesUpdateQueued = std::queue<EntityId>();

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

	entitiesVector[id].entityEventAdd<EntityEvents::EventInitialize>();
	entitiesUpdateQueued.push(id);

	entitiesIntangible.insert(id);

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
	LevelGrid<BaseLevel>::levelGet(level)->entityIdAdd(entityId, (entityGet(entityId).updateType == EntityUpdateType::Frame));
	entitiesIntangible.erase(entityId);

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

void EntityManager::entitiesIntangibleUpdate() {
	std::vector<EntityId> entitiesIntangibleVector(entitiesIntangible.begin(), entitiesIntangible.end());

	for (uint32_t i = 0; i < entitiesIntangibleVector.size(); i++) {
		EntityId id = entitiesIntangibleVector[i];

		if (entitiesVector[id].updateType == EntityUpdateType::Frame) {
			entityUpdate(id);
		}
	}

}

void EntityManager::entitiesQueuedUpdate() {
	while (!entitiesUpdateQueued.empty()) {
		std::cout << "update" << std::endl;
		EntityId entityId = entitiesUpdateQueued.front();
		entitiesUpdateQueued.pop();
		entityUpdate(entityId);
	}
}

