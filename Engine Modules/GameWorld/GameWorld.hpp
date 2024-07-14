#ifndef __GAME_WORLD_H__
#define __GAME_WORLD_H__

#include <vector>
#include <cstdint>
#include <variant>

#include "../ECS/Entities/Entity.hpp"
#include "../ECS/TypeDefinitions.hpp"

#include "LevelTypeDefinitions.hpp"

struct Level {

	Level();
	Level(LevelCoordinate _idX, LevelCoordinate _idY, LevelCoordinate _idZ);
	Level(LevelPosition _id);

	LevelPosition id;

	void entityIdAdd(EntityId id);
	void entityIdRemove(EntityId id);

	// list of EntityIDs belonging to this room 
	std::vector<EntityId> entities;
};

typedef std::unique_ptr<Level> LevelPtr;

using Levels1D = std::vector<LevelPtr>;
using Levels2D = std::vector<Levels1D>;
using Levels3D = std::vector<Levels2D>;

// 3D grid of levels
typedef Levels3D LevelGrid;

namespace GameWorld {
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
	Level* levelGet(LevelCoordinate x, LevelCoordinate y = 0, LevelCoordinate z = 0);
	// get a level at the specified LevelPosition
	Level* levelGet(LevelPosition level);

	// check if a level exists at the specified LevelCoordinates
	bool levelExists(LevelCoordinate x, LevelCoordinate y = 0, LevelCoordinate z = 0);
	// check if a level exists at the specified LevelPosition
	bool levelExists(LevelPosition level);

	// creates a new level at the specified LevelCoordinates and returns a pointer to it so it may be modified
	Level* levelAdd(LevelCoordinate x, LevelCoordinate y = 0, LevelCoordinate z = 0);
	// creates a new level at the specified LevelPosition and returns a pointer to it so it may be modified
	Level* levelAdd(LevelPosition level);

	void levelActivate(LevelCoordinate x, LevelCoordinate y = 0, LevelCoordinate z = 0);
	void levelActivate(LevelPosition level);

	void levelDeactivate(LevelCoordinate x, LevelCoordinate y = 0, LevelCoordinate z = 0);
	void levelDeactivate(LevelPosition level);
};


#endif
