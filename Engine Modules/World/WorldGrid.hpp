#ifndef __WORLD_GRID_H__
#define __WORLD_GRID_H__

#include <vector>
#include <cstdint>
#include <variant>

#include "LevelTypeDefinitions.hpp"
#include "Level.hpp"

using Levels1D = std::vector<LevelPtr>;
using Levels2D = std::vector<Levels1D>;
using Levels3D = std::vector<Levels2D>;

// 3D grid of levels
typedef Levels3D LevelGrid;

namespace WorldGrid {
	// 3D grid of every level in the world.
	// note that, although this is a 3D grid, it's 2nd and 3rd dimensions may be zero,
	// and so it could behave as a simple list, or a 2D grid
	extern LevelGrid levelGrid;

	// list of LevelPositions that are currently active and updating
	extern std::vector<LevelPosition> levelsActiveVector;

	extern LevelPosition levelCur;

	// initialize the level grid and set it to be the dimensions passed in
	void levelGridInitialize(LevelCoordinate width, LevelCoordinate height, LevelCoordinate depth);
	// initialize the level grid and set it to be the dimensions passed in
	void levelGridInitialize(LevelPosition dimensions);

	// get a level at the specified LevelCoordinates
	BaseLevel* levelGet(LevelCoordinate x, LevelCoordinate y = 0, LevelCoordinate z = 0);
	// get a level at the specified LevelPosition
	BaseLevel* levelGet(LevelPosition level);

	// check if a level exists at the specified LevelCoordinates
	bool levelExists(LevelCoordinate x, LevelCoordinate y = 0, LevelCoordinate z = 0);
	// check if a level exists at the specified LevelPosition
	bool levelExists(LevelPosition level);

	// adds a level to the levelGrid.
	// the position the level instance is placed at is the level instance's levelPosition member
	void levelAdd(BaseLevel* levelInstance);

	void levelActivate(LevelCoordinate x, LevelCoordinate y = 0, LevelCoordinate z = 0);
	void levelActivate(LevelPosition level);

	void levelDeactivate(LevelCoordinate x, LevelCoordinate y = 0, LevelCoordinate z = 0);
	void levelDeactivate(LevelPosition level);
};


#endif
