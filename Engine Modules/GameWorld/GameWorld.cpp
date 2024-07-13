#include "GameWorld.hpp"



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


void Level::entitiesUpdate() {
	for (EntityId i = 0; i < entities.size(); i++) {
		//EntityManager
	}
}

void Level::entityIdAdd(const EntityId id) {
	entities.push_back(id);
}
void Level::entityIdRemove(EntityId id) {
	// the position of the id in the entities vector
	auto idVectorPosition = std::find(entities.begin(), entities.end(), id);

	entities.erase(idVectorPosition);
}

LevelGrid GameWorld::levelGrid = LevelGrid(0);

LevelPosition GameWorld::levelCur = LevelPosition(0, 0, 0);

void GameWorld::levelGridInitialize(LevelCoordinate width, LevelCoordinate height, LevelCoordinate depth) {

	if (width == 0) {
		std::cerr << "ERROR: GameWorld initialization failed: levelGrid width cannot be 0" << std::endl;
		return;
	}
	else if (height == 0) {
		if (depth != 0) {
			std::cerr << "ERROR: GameWorld initialization failed: depth cannot be higher than 0 if height is equal to 0" << std::endl;
			return;
		}
	}

	// the whole thing below is just a very annoying and large way of making a 3D grid of LevelPtrs

	// create vector of columns
	Levels3D columns(width);

	for (LevelCoordinate x = 0; x < width; x++) {
		// create vector of rows (every vector of rows takes up an index of the corresponding columns)
		Levels2D rows(height);

		for (LevelCoordinate y = 0; y < height; y++) {
			// create vector of slices(every vector of slices takes up an index of the corresponding row)
			Levels1D slices(depth);

			for (LevelCoordinate z = 0; z < depth; z++) {
				// set the current slice to a ptr of nullptr
				slices[z] = LevelPtr(nullptr);
			}

			// set the current row to slices, which are all ptrs of nullptr
			rows[y] = std::move(slices);
		}

		// set the column to rows, which is a vector of slices of nullptr
		columns[x] = std::move(rows);
	}

	// set levelGrid to columns, where each column is a row, and each row a slice, and each slice a unique_ptr to nullptr
	levelGrid = std::move(columns);
}
void GameWorld::levelGridInitialize(LevelPosition dimensions) {
	levelGridInitialize(dimensions.x, dimensions.y, dimensions.z);
}
Level* GameWorld::levelGet(LevelCoordinate x, LevelCoordinate y, LevelCoordinate z) {
	return levelGrid[x][y][z].get();
}
Level* GameWorld::levelGet(LevelPosition level) {
	return levelGet(level.x, level.y, level.z);
}
bool GameWorld::levelExists(LevelCoordinate x, LevelCoordinate y, LevelCoordinate z) {
	return static_cast<bool>(levelGrid[x][y][z]);
}
bool GameWorld::levelExists(LevelPosition level) {
	return levelExists(level.x, level.y, level.z);
}
Level* GameWorld::levelAdd(LevelCoordinate x, LevelCoordinate y, LevelCoordinate z) {
	Level* levelInstance = new Level(x, y, z);
	levelGrid[x][y][z] = LevelPtr(levelInstance);
	return levelInstance;
}
Level* GameWorld::levelAdd(LevelPosition level) {
	return levelAdd(level.x, level.y, level.z);
}
