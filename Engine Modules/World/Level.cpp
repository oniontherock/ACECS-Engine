#include "Level.hpp"

BaseLevel::BaseLevel() :
	entities(std::vector<EntityId>())
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
	entities.push_back(id);
}
void BaseLevel::entityIdRemove(const EntityId id) {
	// the position of the id in the entities vector
	auto idVectorPosition = std::find(entities.begin(), entities.end(), id);

	if (idVectorPosition == entities.end()) return;

	entities.erase(idVectorPosition);
}
