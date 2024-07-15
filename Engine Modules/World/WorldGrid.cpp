#include "WorldGrid.hpp"


LevelGrid WorldGrid::levelGrid = LevelGrid(0);

std::vector<LevelPosition> WorldGrid::levelsActiveVector = std::vector<LevelPosition>(0);

LevelPosition WorldGrid::levelCur = LevelPosition(0, 0, 0);

void WorldGrid::levelGridInitialize(LevelCoordinate width, LevelCoordinate height, LevelCoordinate depth) {

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
void WorldGrid::levelGridInitialize(LevelPosition dimensions) {
	levelGridInitialize(dimensions.x, dimensions.y, dimensions.z);
}

BaseLevel* WorldGrid::levelGet(LevelCoordinate x, LevelCoordinate y, LevelCoordinate z) {
	return levelGrid[x][y][z].get();
}
BaseLevel* WorldGrid::levelGet(LevelPosition level) {
	return levelGet(level.x, level.y, level.z);
}

bool WorldGrid::levelExists(LevelCoordinate x, LevelCoordinate y, LevelCoordinate z) {
	return static_cast<bool>(levelGrid[x][y][z]);
}
bool WorldGrid::levelExists(LevelPosition level) {
	return levelExists(level.x, level.y, level.z);
}

void WorldGrid::levelAdd(BaseLevel* levelInstance) {
	levelGrid[levelInstance->levelPosition.x][levelInstance->levelPosition.y][levelInstance->levelPosition.z] = LevelPtr(levelInstance);
}

void WorldGrid::levelActivate(LevelCoordinate x, LevelCoordinate y, LevelCoordinate z) {
	
	if (std::find(levelsActiveVector.begin(), levelsActiveVector.end(), LevelPosition(x, y, z)) != levelsActiveVector.end()) return;

	levelsActiveVector.push_back(LevelPosition(x, y, z));
}
void WorldGrid::levelActivate(LevelPosition level) {
	levelActivate(level.x, level.y, level.z);
}

void WorldGrid::levelDeactivate(LevelCoordinate x, LevelCoordinate y, LevelCoordinate z) {
	levelsActiveVector.erase(std::find(levelsActiveVector.begin(), levelsActiveVector.end(), LevelPosition(x, y, z)));
}
void WorldGrid::levelDeactivate(LevelPosition level) {
	levelDeactivate(level.x, level.y, level.z);
}
