#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "../ECS/TypeDefinitions.hpp"
#include "LevelTypeDefinitions.hpp"
#include <iostream>
#include <vector>


struct BaseLevel {

	BaseLevel();
	BaseLevel(LevelCoordinate _idX, LevelCoordinate _idY, LevelCoordinate _idZ);
	BaseLevel(LevelPosition _id);

	LevelPosition levelPosition;

	void entityIdAdd(EntityId id, bool frameUpdate);
	void entityIdRemove(const EntityId id);

	bool isUpdating;

	// list of EntityIDs belonging to this room 
	std::vector<EntityId> entities;
	// list of EntityIDs belonging to this room whose update type is not Frame
	std::vector<EntityId> entitiesNoUpdate;
};

template <class Level>
using LevelPtr = std::unique_ptr<Level>;

using BaseLevelPtr = LevelPtr<BaseLevel>;

#endif
