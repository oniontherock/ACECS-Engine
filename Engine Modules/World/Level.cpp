#include "Level.hpp"


Level::Level() :
	entities(std::vector<EntityId>())
{}

Level::Level(LevelCoordinate _idX, LevelCoordinate _idY, LevelCoordinate _idZ) :
	Level()
{
	id = LevelPosition(_idX, _idY, _idZ);
}

Level::Level(LevelPosition _id) :
	Level(_id.x, _id.y, _id.z)
{}

void Level::entityIdAdd(const EntityId id) {
	entities.push_back(id);
}
void Level::entityIdRemove(EntityId id) {
	// the position of the id in the entities vector
	auto idVectorPosition = std::find(entities.begin(), entities.end(), id);

	entities.erase(idVectorPosition);
}
