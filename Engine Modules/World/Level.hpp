#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "LevelTypeDefinitions.hpp"
#include "../ECS/Entities/Entity.hpp"
#include "../ECS/TypeDefinitions.hpp"

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

#endif