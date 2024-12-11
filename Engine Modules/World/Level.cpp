#include "Level.hpp"
#include "../ECS/Entities/EntityManager.hpp"

BaseLevel::BaseLevel() :
	entities(std::vector<EntityId>()),
	isUpdating(true)
{}

BaseLevel::BaseLevel(LevelCoordinate _idX, LevelCoordinate _idY, LevelCoordinate _idZ) :
	BaseLevel()
{
	levelPosition = LevelPosition(_idX, _idY, _idZ);
}

BaseLevel::BaseLevel(LevelPosition _id) :
	BaseLevel(_id.x, _id.y, _id.z)
{}

void BaseLevel::entityIdAdd(EntityId id) {
	bool frameUpdate = EntityManager::entityGet(id).updateType == EntityUpdateType::Frame;

	if (frameUpdate) entities.push_back(id);
	else entitiesNoUpdate.push_back(id);
}
void BaseLevel::entityIdRemove(const EntityId id) {

	bool frameUpdate = EntityManager::entityGet(id).updateType == EntityUpdateType::Frame;

	if (frameUpdate) {
		// the position of the id in the entities vector
		auto idVectorPosition = std::find(entities.begin(), entities.end(), id);

		if (idVectorPosition != entities.end()) {
			entities.erase(idVectorPosition);
		}
	}
	else {
		// the position of the id in the entitiesNoUpdate vector
		auto idVectorPosition = std::find(entitiesNoUpdate.begin(), entitiesNoUpdate.end(), id);

		if (idVectorPosition == entitiesNoUpdate.end()) {
			entitiesNoUpdate.erase(idVectorPosition);
		}
	}
}
