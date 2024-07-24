#ifndef __WORLD_GRID_H__
#define __WORLD_GRID_H__

#include <vector>
#include <cstdint>
#include <variant>

#include "LevelTypeDefinitions.hpp"
#include "Level.hpp"

using Levels1D = std::vector<BaseLevelPtr>;
using Levels2D = std::vector<Levels1D>;
using Levels3D = std::vector<Levels2D>;

// 3D grid of levels
using BaseLevelPtrGrid = Levels3D;

extern BaseLevelPtrGrid levelGrid;

template <class Level>
struct LevelGrid {
	// 3D grid of every level in the world.
	// note that, although this is a 3D grid, it's 2nd and 3rd dimensions may be zero,
	// and so it could behave as a simple list, or a 2D grid

	// list of LevelPositions that are currently active and updating
	static std::vector<LevelPosition> levelsActiveVector;

	static LevelPosition levelCur;

	// initialize the level grid and set it to be the dimensions passed in
	static void levelGridInitialize(LevelCoordinate width, LevelCoordinate height, LevelCoordinate depth) {

		if (width == 0) {
			std::cerr << "ERROR: LevelGrid initialization failed: levelGrid width cannot be 0" << std::endl;
			return;
		}
		else if (height == 0) {
			if (depth != 0) {
				std::cerr << "ERROR: LevelGrid initialization failed: depth cannot be higher than 0 if height is equal to 0" << std::endl;
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
					slices[z] = BaseLevelPtr(nullptr);
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
	// initialize the level grid and set it to be the dimensions passed in
	static void levelGridInitialize(LevelPosition dimensions) {
		levelGridInitialize(dimensions.x, dimensions.y, dimensions.z);
	}

	// get a level at the specified LevelCoordinates
	static Level* levelGet(LevelCoordinate x, LevelCoordinate y = 0, LevelCoordinate z = 0) {
		return static_cast<Level*>(levelGrid[x][y][z].get());
	}
	// get a level at the specified LevelPosition
	static Level* levelGet(LevelPosition level) {
		return levelGet(level.x, level.y, level.z);
	}

	// check if a level exists at the specified LevelCoordinates
	static bool levelExists(LevelCoordinate x, LevelCoordinate y = 0, LevelCoordinate z = 0) {
		return static_cast<bool>(levelGrid[x][y][z]);
	}
	// check if a level exists at the specified LevelPosition
	static bool levelExists(LevelPosition level) {
		return levelExists(level.x, level.y, level.z);
	}

	// adds a level to the levelGrid.
	// the position the level instance is placed at is the level instance's levelPosition member
	static void levelAdd(BaseLevel* levelInstance) {
		levelGrid[levelInstance->levelPosition.x][levelInstance->levelPosition.y][levelInstance->levelPosition.z] = BaseLevelPtr(levelInstance);
	}

	static void levelActivate(LevelCoordinate x, LevelCoordinate y = 0, LevelCoordinate z = 0) {

		if (std::find(levelsActiveVector.begin(), levelsActiveVector.end(), LevelPosition(x, y, z)) != levelsActiveVector.end()) return;

		levelsActiveVector.push_back(LevelPosition(x, y, z));
	}
	static void levelActivate(LevelPosition level) {
		levelActivate(level.x, level.y, level.z);
	}

	static void levelDeactivate(LevelCoordinate x, LevelCoordinate y = 0, LevelCoordinate z = 0) {
		levelsActiveVector.erase(std::find(levelsActiveVector.begin(), levelsActiveVector.end(), LevelPosition(x, y, z)));
	}
	static void levelDeactivate(LevelPosition level) {
		levelDeactivate(level.x, level.y, level.z);
	}
};

#endif
